/*
 * CAN.c
 *
 * Created: 13.10.2016 17:26:28
 *  Author: Whiskey Dicks
 */


// 

#include "CAN.h"
#include "bit_macros.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/delay.h>

volatile uint8_t flag = 0;


ISR(INT2_vect){
	//printf("int\n");
	flag = 1;
}

void can_init(uint8_t mode){
	
	mcp_2515_init(mode);
	
	mcp_2515_write(MCP_CANINTE, MCP_RX_INT);
	
	// Disable global interrupts
	cli();
	// Interrupt on falling edge
	set_bit(EICRA, ISC21);
	clear_bit(EICRA, ISC20);
	// Enable interrupt
	set_bit(EIMSK,INT2);
	// Enable global interrupts
	sei();
	
}

uint8_t can_interrupt(){
	if (flag){
		flag = 0;
		return 1;
	}
	return 0;
}

void can_handle_messages(){
	uint8_t v[2] = {0};
	
	can_int_vect(v);
	can_message message1;
	
	if (v[0]){
		printf("  INCOMING MESSAGE\n");
		printf("|  buffer\t| length\t|     ID\t|\n");
		printf("|  RXB0\t|      %u \t|   %u \t|\n\n", message1.length, message1.id);
		can_message_receive(0, &message1);
		//printf("ID: %u\n", message1.id);
		printf("  MSG:\t    |");
		for (uint8_t i = 0; i < message1.length; i++){
			printf(" %d |", message1.data[i]);
		}
		printf("\n\n\n");
	}
	
	can_int_vect(v);
	can_message message2;
	
	if (v[1]){
		printf("  INCOMING MESSAGE\n");
		printf("|    buff\t|     ID\t|    len\t|\n");
		printf("|  RXB1\t|   %u \t|      %u \t|\n\n", message2.id, message2.length);
		can_message_receive(1, &message2);
		printf("|   msg\t|");
		for (uint8_t i = 0; i < message2.length; i++){
			printf(" %d | ", message2.data[i]);
		}
		printf("\n\n\n");
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
	id_low = id_low*0b100000;
	mcp_2515_write(MCP_TXB0SIDH + 16 * buffer_number, id_high);
	mcp_2515_write(MCP_TXB0SIDL + 16 * buffer_number, id_low);
	
	// Define data length of message
	uint8_t data_length = message->length;
	mcp_2515_write(MCP_TXB0DLC + 16 * buffer_number, data_length);
	
	// Write data bytes to transmit buffer
	char* data_bytes = message->data;
	for (uint8_t byte = 0; byte < data_length; byte++) {
		mcp_2515_write(MCP_TXB0Dm + byte + 16 * buffer_number, data_bytes[byte]);
	}
	
	// Request to send message, send if successful
	mcp_2515_request_to_send(MCP_RTS_TX0 + buffer_number);
	
}

int can_transmit_complete(int buffer_number){
	uint8_t transmit_flag = mcp_2515_read(MCP_CANINTF);
	uint8_t interrupt_bits = (transmit_flag & (MCP_TX0IF + buffer_number*2));
	
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
	received_message->id = 0b1000*id_high + id_low/0b100000;
	
	uint8_t data_length = mcp_2515_read(MCP_RXB0DLC + 16 * rec_buff_num);
	mask = 0b1111;
	received_message->length = (data_length & mask);
	
	for (int8_t byte = 0; byte < data_length; byte++) {
		received_message->data[byte] = (int8_t)mcp_2515_read(MCP_RXB0DM + byte + 16 * rec_buff_num);
	}
	
	
}

void can_int_vect(uint8_t* v) { 
	uint8_t int_flag = mcp_2515_read(MCP_CANINTF);
	v[0] = (int_flag & MCP_RX0IF);
	v[1] = (int_flag & MCP_RX1IF);
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