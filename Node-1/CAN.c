/*
 * CAN.c
 *
 * Created: 13.10.2016 17:26:28
 *  Author: Whiskey Dicks
 */


// 

#include "CAN.h"
#include "MCP2515.h"
#include "bit_macros.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/delay.h>

volatile int flag = 0;


ISR(INT0_vect){
	printf("interrupt");
	flag = 1;
}

void can_init(){
	printf("WHERE");
	

	mcp_2515_init();
	printf("DO");
	
	mcp_2515_write(MCP_CANINTE, MCP_RX_INT);
	printf("YOU");
	// Disable global interrupts
	cli();
	// Interrupt on falling edge PD2
	set_bit(MCUCR, ISC01);
	clear_bit(MCUCR, ISC00);
	// Enable interrupt on PD2
	set_bit(GICR,INT0);
	// Enable global interrupts
	sei();
	printf("FUCK UP");
	
	
}

int can_interrupt(){
	if (flag){	
		flag = 0;
		return 1;
	}
	return 0;
}

void can_handle_messages(){
	
	int v[2] = {0};
	
	can_int_vect(v);
	
	can_message *message1;
	can_message *message2;
	
	if (v[0]){
		printf("RXB0\n");
		can_message_receive(0, &message1);
		int length = message1->length;
		for (uint8_t i = 0; i < length; i++){
			uint8_t data = message1->data[i];
			printf("data %d: %c\n",i, data);
		}
	}
	
	if (v[1]){
		printf("RXB1\n");
		can_message_receive(1, &message2);
		for (uint8_t i = 0; i < message2->length; i++){
			printf("data %d: %c\n",i, &message2->data[i]);
		}
	}
	
	mcp_2515_bit_modify(MCP_CANINTF, 3, 0);
}

void can_message_send(can_message* message){
	static int buffer_number = 0;
	
	buffer_number +=1;
	if (buffer_number > 2) {
		buffer_number = 0;
	}
	
	while (!can_transmit_complete(buffer_number)){
		buffer_number +=1;
		if (buffer_number > 2) {
			buffer_number = 0;
		}
	}
	
	// Arbitration field identifier
	unsigned int ID = message->id;
	char id_high = ID / 8;
	char id_low = ID % 8;
	id_low = id_low*2^5;
	mcp_2515_write(MCP_TXB0SIDH + 16 * buffer_number, id_high);
	mcp_2515_write(MCP_TXB0SIDL + 16 * buffer_number, id_low);
	
	// Define data length of message
	int data_length = message->length;
	mcp_2515_write(MCP_TXB0DLC + 16 * buffer_number, data_length);
	
	// Write data bytes to transmit buffer
	char* data_bytes = message->data;
	for (int byte = 0; byte < data_length; byte++) {
		mcp_2515_write(MCP_TXB0Dm + byte + 16 * buffer_number, data_bytes[byte]);
	}
	
	// Request to send message, send if successful
	mcp_2515_request_to_send(MCP_RTS_TX0 + buffer_number);
	
}

int can_transmit_complete(int buffer_number){
	uint8_t flag = mcp_2515_read(MCP_CANINTF);
	uint8_t interrupt_bits = (flag & (MCP_TX0IF + buffer_number*2));
	
	if(interrupt_bits == (MCP_TX0IF + buffer_number*2)){
			return 0;
	}
	return 1;
}

void can_message_receive(int rec_buff_num, can_message* received_message){
	uint8_t id_high = mcp_2515_read(MCP_RXB0SIDH + 16 * rec_buff_num);
	uint8_t id_low = mcp_2515_read(MCP_RXB0SIDL + 16 * rec_buff_num);
	uint8_t mask = 0b11100000;
	id_low = (id_low & mask);
	received_message->id = 0b1000*id_high + id_low;
	
	int data_length = mcp_2515_read(MCP_RXB0DLC + 16 * rec_buff_num);
	mask = 0b1111;
	received_message->length = (data_length & mask);
	
	
	for (int byte = 0; byte < data_length; byte++) {
		received_message->data[byte] = mcp_2515_read(MCP_RXB0DM + byte + 16 * rec_buff_num);
	}
	
	
}

void can_int_vect(int* v) { 
	uint8_t flag = mcp_2515_read(MCP_CANINTF);
	v[0] = (flag & MCP_RX0IF);
	v[1] = (flag & MCP_RX1IF);
}

int can_error(void){
	uint8_t err = mcp_2515_read(MCP_CANINTF);
	uint8_t mask = 0b00100000;
	if (mask & err == mask){
		printf("Error in CAN!\n");
		mcp_2515_bit_modify(MCP_CANINTF,mask,0);
		return 1;
	}
	return 0;
}

//Hvis det nye brettet ikke funker, sett PB0 på Arduinoen til 1!!!!!!!!!!!!!