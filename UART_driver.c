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

#define BAUD 9600 //Baud rate = symbols pr second

void UART_init(unsigned int clock_speed){
	/*
	Trengs dette?
	DDRD |= (0 << PD0)			//0 sets port PD0 to output mode. PD1 is transmitter.
	DDRD |= (1 << PD1)			//1 sets port PD1 to input mode. PD2 is receiver.
	*/
	
	unsigned char ubrr = clock_speed / (BAUD * 16) - 1;	//USART Baud Rate Register 
	
	UBRR0H = ubrr >> 8;			// Save the most significant bits (4 most sign. bits out of 12 bits)
	UBRR0L = ubrr;				// Save the least sign. bits (8 least sign. bits)
	
	set_bit(UCSR0B,RXEN0);		//RXEN enables the receiver.
	set_bit(UCSR0B,TXEN0);		//TXEN enables the transmitter.
	
	// Set frame format
	set_bit(UCSR0C,URSEL0);		// URSEL: 1 = Choose UCSRC register instead of UBRRH register
	clear_bit(UCSR0C,UMSEL0);	// UMSEL: 0 = Asynchronous operation, not synchronous
	set_bit(UCSR0C,USBS0);		// USBS: 1 = Use 2 stop bits, not 1
	set_bit(UCSR0C,UCSZ00);		// UCSZ0: 1
	set_bit(UCSR0C,UCSZ10);		// UCSZ1: 1 = Use 8 bits (11 binary) for each character
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
