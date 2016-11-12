/*
 * DAC_driver.c
 *
 * Created: 05.11.2016 18:49:35
 *  Author: Whiskey dick
 */ 

#include <stdint.h>
#include <avr/interrupt.h>
#include "TWI_Master.h"

void DAC_init() {
	sei();
	TWI_Master_Initialise();
}

void DAC_send(uint8_t data) {
	uint8_t address = 0b01010000;
	uint8_t command = 0b0;
	
	uint8_t message[3];
	message[0] = address;
	message[1] = command;
	message[2] = data;
	
	TWI_Start_Transceiver_With_Data(message, 3);
}