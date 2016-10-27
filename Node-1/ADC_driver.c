/*
 * ADC.c
 *
 * Created: 15.09.2016 15:46:33
 *  Author: Whiskey Dicks
 */
#include <stdlib.h>
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include "bit_macros.h"
#include "ADC_driver.h"
#include "joystick_driver.h"

#ifndef ADC_ADDRESS
#define ADC_ADDRESS 0x1400
#endif

volatile char* ext_adc = ADC_ADDRESS;	//Create a pointer to the array of all addresses we will write to. ADC starting at 0x1400.
volatile char ADC_data;

/*
Chip select settes lav hele tiden, kan det være et problem?
*/

//volatile int new_data = 0;

ISR(INT1_vect){
	
	ADC_data = ext_adc[0x00];
	
//	new_data = 1;
}

void ADC_init(void){
	
	//INITIALIZE INTERRUPT ON PIN PD3

	// Button input
	clear_bit(DDRD, PD3);
	set_bit(PORTD, PD3);	//Set pull-up resistor
	// Disable global interrupts
	cli();
	// Interrupt on falling edge PD3
	set_bit(MCUCR, ISC11);
	clear_bit(MCUCR, ISC10);
	// Enable interrupt on PD3
	set_bit(GICR,INT1);
	// Enable global interrupts
	sei();
}

char get_ADC_data(void){
// 	printf("hei\n");
// 	while(!new_data){printf("DEN ER FOR TREIG");}
// 	new_data = 0;
	//printf("get data\n");
	//printf("Return data %d\n",ADC_data);
	return ADC_data;
}

void ADC_start_read(channel_t channel){
	
	char data = 0x00;
	
	switch (channel) {
		case CHANNEL1 :
			data = 0x04;
			break;
		case CHANNEL2 :
			data = 0x05;
			break;
		case CHANNEL3 :
			data = 0x06;
			break;
		case CHANNEL4 : 
			data = 0x07;
			break;
		default:
			printf("Not valid channel");
			return EXIT_FAILURE;
	}
	
	ext_adc[0x00] = data;
	
}