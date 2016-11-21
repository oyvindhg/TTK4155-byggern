/*
 * UART_driver.c
 *
 * Created: 20.11.2016	22:57:34
 *  Author: Whiskey dicks
 */

// UART = Universal Asynchronous Receiver/Transmitter

#include <stdio.h>
#include <avr/io.h>
#include "bit_macros.h"
#include "UART_driver.h"

#define BAUD 9600 //Baud rate = symbols pr second.

void UART_init_3(unsigned long clock_speed){
	
	unsigned long baud = BAUD;
	unsigned char ubrr = (clock_speed / (baud * 16)) - 1;
	
	/* Set baud rate */
	UBRR3H = ubrr >> 8;			// Save the most significant bits (4 most sign. bits out of 12 bits)
	UBRR3L = ubrr;				// Save the least sign. bits (8 least sign. bits)
	
	/* Set frame format: 8data, 2stop bit */
	UCSR3C = (1<<USBS3);		// USBS: 1 = Use 2 stop bits, not 1												
	UCSR3C = (3<<UCSZ30);		// UCSZ00: 3 - UCSZ0 and UCSZ1 defines 8 bits (11 binary) for each character	
	
	/* Enable receiver and transmitter */
	set_bit(UCSR3B,RXEN3);		//RXEN enables the receiver.
	set_bit(UCSR3B,TXEN3);		//TXEN enables the transmitter.
	
}

int put_char_3(unsigned char c){
/*	printf("testing\n");*/
	loop_until_bit_is_set(UCSR3A, UDRE3);
/*	printf("Success!\n");*/
	UDR3 = c;
	return 0;
}

int get_char_3(void){
	loop_until_bit_is_set(UCSR3A, RXC3);

	return UDR3;
}