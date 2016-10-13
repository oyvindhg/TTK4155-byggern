/*
 * CAN.c
 *
 * Created: 13.10.2016 17:26:28
 *  Author: Whiskey Dicks
 */


#include "CAN.h"
#include "MCP2515.h"

#include <avr/io.h>

int buffer_number = 0;		//0 is the first register, 1 is the second register and 3 is the last register

void can_init(void){
	int a = 0;
}

void can_message_send(can_message* message){
	
	unsigned int ID = message->id;
	
	char id_low = ID % 8;
	
	id_low = id_low*2^5;
	char id_high = ID / 8;
	
	mcp_2515_write(0x31 + 16 * buffer_number, id_high);
	mcp_2515_write(0x32 + 16 * buffer_number, id_low);
	
	int len = message->length;
	//RTR in this register! RTR is now 0, should be 1 later??
	int RTR = 0;
	mcp_2515_write(0x35 + 16 * buffer_number, len + RTR * 2^6);
	
	char* data_bytes = message->data;
	
	for (int i = 0; i < len; i++) {
		mcp_2515_write(0x36+i + 16 * buffer_number, data_bytes[i]);
	}
	
	
	mcp_2515_request_to_send(MCP_RTS_TX0 + buffer_number);
}