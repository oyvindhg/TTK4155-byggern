/*
 * CAN_controller_driver.c
 *
 * Created: 13.10.2016 09:07:30
 *  Author: Whiskey Dicks
 */

#include "CAN_controller_driver.h"
#include "MCP2515.h"
#include "bit_macros.h"

#include <avr/io.h>
// #include <avr/delay.h>

// Ok to clear_bit and set_bit PB4 in SPI?
// How can it recognize MCP_RESET without including MCP2515.h?

void mcp_activate_slave(){
	/* Activate Slave Select */
	clear_bit(PORTB, PB4);
}


void mcp_deactivate_slave(){
	/* Deactivate Slave Select */
	set_bit(PORTB, PB4);
}

void mcp_2515_set_mode(uint8_t mode){
	mcp_2515_write(MCP_CANCTRL, mode);
}

uint8_t mcp_2515_init(){
	
	uint8_t val;
	SPI_init();
	
	mcp_2515_reset();
	//_delay_ms(0.003); Trenger vi delay etter reset som det står i databladet???
	
	val = mcp_2515_read(MCP_CANSTAT);
	uint8_t mode_bits = (val & MODE_MASK);
	if(mode_bits != MODE_CONFIG){
		printf("MCP2515 is NOT in Configuration mode after reset! Its config bits are %x\n", mode_bits);
		return 1;
	}
	
	mcp_2515_set_mode(MODE_LOOPBACK);

	val = mcp_2515_read(MCP_CANSTAT);
	mode_bits = (val & MODE_MASK);
	if(mode_bits != MODE_LOOPBACK){
		printf("MCP2515 is NOT in loopback mode after reset! Its config bits are %x\n", mode_bits);
		return 1;
	}
	
	
	return 0;
}

void mcp_2515_reset(){
	mcp_activate_slave();
	SPI_write(MCP_RESET);
	mcp_deactivate_slave();
}

uint8_t mcp_2515_read(uint8_t address){
	mcp_activate_slave();
	
	uint8_t data;
	
	SPI_write(MCP_READ);
	SPI_write(address);
	data = SPI_read();
	
	mcp_deactivate_slave();
	
	return data;
}


void mcp_2515_write(uint8_t address, uint8_t data) {
	mcp_activate_slave();
	
	SPI_write(MCP_WRITE);
	SPI_write(address);
	SPI_write(data);
	
	mcp_deactivate_slave();
}

void mcp_2515_request_to_send(char buffer) {
	mcp_activate_slave();
	
	SPI_write(buffer);
	
	mcp_deactivate_slave();
}

void mcp_2515_bit_modify(uint8_t adress, uint8_t mask, uint8_t data) {
	mcp_activate_slave();
	
	SPI_write(MCP_BITMOD);
	SPI_write(adress);
	SPI_write(mask);
	SPI_write(data);
	
	mcp_deactivate_slave();
}

uint8_t mcp_2515_read_status() {
	mcp_activate_slave();
	
	SPI_write(MCP_READ_STATUS);
	uint8_t status = SPI_read();
	
	mcp_deactivate_slave();
	
	return status;
}