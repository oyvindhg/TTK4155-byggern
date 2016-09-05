/*
 * UART_driver.c
 *
 * Created: 03.09.2016 16:32:20
 *  Author: Whiskey dicks
 */

// Er URSEL 0 by default?? altså skrive til UBRRH

// UART = Universal Asynchronous Receiver/Transmitter

#include <avr/io.h>
#include "bit_macros.h"

#define BAUD 9600 //Baud rate = symbols pr second. Passende med 9600?

void UART_init(unsigned long clock_speed){
	
	//Er dette riktig?
	clear_bit(DDRD,PD0);			//0 sets pin PD0 (RXD0) to input mode. PD0 is receiver.
	set_bit(DDRD,PD1);				//1 sets pin PD1 (TXD0) to output mode. PD1 is transmitter.
	
	unsigned char ubrr = clock_speed / (BAUD * 16) - 1;	//USART Baud Rate Register. Alltid et helt tall? 
	
	UBRR0H = ubrr >> 8;			// Save the most significant bits (4 most sign. bits out of 12 bits)
	UBRR0L = ubrr;				// Save the least sign. bits (8 least sign. bits)
	
	set_bit(UCSR0B,RXEN0);		//RXEN enables the receiver.
	set_bit(UCSR0B,TXEN0);		//TXEN enables the transmitter.
	
	// Set frame format
	set_bit(UCSR0C,URSEL0);		// URSEL: 1 = Choose UCSRC register instead of UBRRH register
	clear_bit(UCSR0C,UMSEL0);	// UMSEL: 0 = Asynchronous operation, not synchronous
	set_bit(UCSR0C,USBS0);		// USBS: 1 = Use 2 stop bits, not 1
	set_bit(UCSR0C,UCSZ00);		// UCSZ0: 1
	set_bit(UCSR0C,UCSZ10);		// UCSZ1: 1		-	 UCSZ0 and UCSZ1 defines 8 bits (11 binary) for each character
}

int put_char(unsigned char c){
	loop_until_bit_is_set(UCSR0A, TXC0);
	UDR0 = c;
	return 0;
}

unsigned char get_char(){
	//loop_until_bit_is_set(UCSRA, RXS);
	
	if test_bit(UCSR0A, RXC0)
		return UDR0;
	return 0x00;
}
