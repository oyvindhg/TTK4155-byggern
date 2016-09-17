/*
 * ADC.c
 *
 * Created: 15.09.2016 15:46:33
 *  Author: Whiskey Dicks
 */
#include <stdlib.h>
#include <stdint.h>
#include "ADC_driver.h"

#ifndef ADC_FIRST_ADDRESS
#define ADC_FIRST_ADDRESS 0x1400	//This is just a macro, it has no data type.
#endif

void ADC_init(void){
	
	//INITIALIZE INTERRUPT ON PIN 
	
	// Button input
	DDRE &= ~(1<<PE0);					// Bruke Int1 her??
	// Disable global interrupts
	cli();
	// Interrupt on rising edge PE0
	EMCUCR |= (1<<ISC2);
	// Enable interrupt on PE0
	GICR |= (1<<INT2);
	// Enable global interrupts
	sei();
	
	
}


void ADC_start_read(int channel){
	
	volatile char* ext_adc = ADC_FIRST_ADDRESS;	//Create a pointer to the array of all addresses we will write to. SRAM starting at 0x1800. ext_ram[0x7FF] is maximum because 0x1800 + 0x7FF = 0x1FFF!
	
	address = 0x000;
	
	switch case(channel){
		case 1:
			data = 0x04;
			break;
		case 2:
			data = 0x05;
			break;
		case 3:
			data = 0x06;
			break;
		default:
			printf("Not valid channel");
			return EXIT_FAILURE;
	}
	
	ext_adc[address] = data;
	
}