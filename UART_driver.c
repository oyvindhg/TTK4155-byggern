/*
 * UART_driver.c
 *
 * Created: 03.09.2016 16:32:20
 *  Author: Whiskey dicks
 */

// Er URSEL 0 by default?? altså skrive til UBRRH

// UART = Universal Asynchronous Receiver/Transmitter

#include <avr/io.h>
#include <stdio.h>
#include "bit_macros.h"
#include "UART_driver.h"

#define BAUD 9600 //Baud rate = symbols pr second.

void UART_init(unsigned long clock_speed){
	
	//Er dette riktig?
	//clear_bit(DDRD,PD0);			//0 sets pin PD0 (RXD0) to input mode. PD0 is receiver.
	//set_bit(DDRD,PD1);				//1 sets pin PD1 (TXD0) to output mode. PD1 is transmitter.

	unsigned long baud = BAUD;
	unsigned char ubrr = (clock_speed / (baud * 16)) - 1;	//Should be, and is, 31
	
	/* Set baud rate */
	UBRR0H = ubrr >> 8;			// Save the most significant bits (4 most sign. bits out of 12 bits)
	UBRR0L = ubrr;				// Save the least sign. bits (8 least sign. bits)
	
	/* Set frame format: 8data, 2stop bit */
	UCSR0C = (1<<URSEL0)|(1<<USBS0);		// USBS: 1 = Use 2 stop bits, not 1												!!!! REMEMBER THAT URSEL0 MUST BE SET FOR EVERY PIN CHANGE
	UCSR0C = (1<<URSEL0)|(3<<UCSZ00);		// UCSZ00: 3 - UCSZ0 and UCSZ1 defines 8 bits (11 binary) for each character	!!!! REMEMBER THAT URSEL0 MUST BE SET FOR EVERY PIN CHANGE
	
	/* Enable receiver and transmitter */
	set_bit(UCSR0B,RXEN0);		//RXEN enables the receiver.
	set_bit(UCSR0B,TXEN0);		//TXEN enables the transmitter.
	
	fdevopen(put_char, get_char);
	
}

int put_char(unsigned char c){
	loop_until_bit_is_set(UCSR0A, UDRE0);
	/*UCSR0B &= ~(1<<TXB80);
	if ( c & 0x0100 )
	UCSR0B |= (1<<TXB80);*/
	UDR0 = c;
	return 0;
}

int get_char(void){
	loop_until_bit_is_set(UCSR0A, RXC0);
	
	//if test_bit(UCSR0A, RXC0)
	return UDR0;
}