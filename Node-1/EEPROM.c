/*
 * EEPROM.c
 *
 * Created: 20.11.2016 10:25:29
 *  Author: WD 
 */ 

#include "EEPROM.h"
#include "bit_macros.h"

#include <avr/io.h>
#include <avr/interrupt.h>

void EEPROM_write(uint8_t address, uint8_t data){
	
	//Disable interrupts
	cli();
	
	// Wait for previous write to finish
	loop_until_bit_is_clear(EECR, EEWE);
	
	// Set up address registers
	clear_bit(EEARH, 0);
	EEARL = address;
	
	// Set up data register
	EEDR = data;
	
	// Start write
	set_bit(EECR, EEMWE);
	set_bit(EECR, EEWE);
	
	//Enable interrupts
	sei();
}

uint8_t EEPROM_read(uint8_t address){
	
	// Disable interrupts
	cli();
	
	// Wait for previous write to finish
	loop_until_bit_is_clear(EECR, EEWE);

	// Set up address registers
	clear_bit(EEARH, 0);
	EEARL = address;
	
	// Start reading by writing EERE
	set_bit(EECR, EERE);
	
	uint8_t ret_data;

	// Return data from data register
	ret_data = EEDR;
	
	//Enable interrupts
	sei();
	
	return ret_data;
	
}

void EEPROM_reset(uint8_t num){
	
	for (uint8_t i = 0; i < num; i++){
		EEPROM_write(i,0);	
	}
		
}