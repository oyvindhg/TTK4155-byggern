/*
 * solenoid_driver.c
 *
 * Created: 10.11.2016 12:52:31
 *  Author: oyvindhg
 */ 

#define F_CPU 16000000

#include "bit_macros.h"
#include "solenoid_driver.h"

#include <avr/delay.h>
#include <avr/io.h>

void solenoid_init(){
	
	// Set pin A1 to output
	set_bit(DDRF, PF1);
	set_bit(PORTF, PF1);
}

void solenoid_shoot(){
	
	// Set a pulse on pin A1
	clear_bit(PORTF, PF1);
	_delay_ms(50);
	set_bit(PORTF, PF1);
}