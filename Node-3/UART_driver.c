/*
 * UART_driver.c
 *
 * Created: 03.09.2016 16:32:20
 *  Author: Whiskey dicks
 */

// UART = Universal Asynchronous Receiver/Transmitter

#include <avr/io.h>
#include "bit_macros.h"
#include "UART_driver.h"

#define BAUD 9600 //Baud rate = symbols pr second.

void UART_init(unsigned long clock_speed){
	
	unsigned long baud = BAUD;
	unsigned char ubrr = (clock_speed / (baud * 16)) - 1;	//Should be, and is, 31
	
	/* Set baud rate */
	UBRR0H = ubrr >> 8;			// Save the most significant bits (4 most sign. bits out of 12 bits)
	UBRR0L = ubrr;				// Save the least sign. bits (8 least sign. bits)
	
	/* Set frame format: 8data, 2stop bit */
	UCSR0C = (1<<USBS0);		// USBS: 1 = Use 2 stop bits, not 1												
	UCSR0C = (3<<UCSZ00);		// UCSZ00: 3 - UCSZ0 and UCSZ1 defines 8 bits (11 binary) for each character	
	
	/* Enable receiver and transmitter */
	set_bit(UCSR0B,RXEN0);		//RXEN enables the receiver.
	set_bit(UCSR0B,TXEN0);		//TXEN enables the transmitter.
	
}

int put_char(unsigned char c){
	loop_until_bit_is_set(UCSR0A, UDRE0);
	UDR0 = c;
	return 0;
}

char get_char(void){
	loop_until_bit_is_set(UCSR0A, RXC0);

	return UDR0;
}

char get_char_imm(void) {
	return UDR0;
}