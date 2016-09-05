/*
 * main.c
 *
 * Created: 03.09.2016 12:26:04
 *  Author: Whiskey dicks
 
 Crystal oscillator frequency: 4.9152 MHz
 
 Use external reset?
 DIP eller SO?
 Klokka føkka - 1000 ms git 400 ms periode
 
 Hva er MAXIM233??
 
 */ 

#ifndef F_CPU
#define F_CPU 4915200UL	//Settes den i hele prosjektet?
#endif

#include <avr/io.h>
#include <util/delay.h>

#include "bit_macros.h"
#include "UART_driver.h"

//#define DDRB |= (1 << PB1)		// Data direction register B. 1 sets port PB1 to output mode.
//Funker dette? Ser ikke forskjell

int main(void) {
	
	UART_init(F_CPU);
	
	while(1) {
	//Test klokkefart	
	/*	_delay_ms(1000);			//ms
		
		toggle_bit(PORTB, PB1); */
		
		_delay_ms(500);

		//if (get_char() == 0x00){
		//	toggle_bit(PORTB, PB1);
		//	}

		put_char('c');
	}
	//return 0;
}