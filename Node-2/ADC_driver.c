/*
 * ADC.c
 *
 * Created: 03.11.2016 19:56:04
 *  Author: whiskey dicks
 */ 

#include <AVR/io.h>

#include "bit_macros.h"
#include "ADC_driver.h"

void ADC_init() {
	// Set pin A2 to input
	clear_bit(DDRF, PF2);
	
	// Enable ADC
	set_bit(ADCSRA, ADEN);
	// Set prescaler to 128
	set_bit(ADCSRA, ADPS0);
	set_bit(ADCSRA, ADPS1);
	set_bit(ADCSRA, ADPS2);
	// Set voltage reference to 2.56V
	set_bit(ADMUX,REFS1);
	set_bit(ADMUX,REFS0);
	
	ADC_read();	
}

uint16_t ADC_read() {
	
	uint16_t data = 0;
	//Read from ADC2
	set_bit(ADMUX, MUX1);
	// Start conversion
	set_bit(ADCSRA,ADSC);
	// Wait for conversion complete
	loop_until_bit_is_set(ADCSRA,ADIF);
	// Read data
	uint8_t data_low = ADCL;
	uint16_t data_high = ADCH;
	data = data_low + data_high*0b100000000;
	
	return data;
}