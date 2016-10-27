/*
 * Byggern_gr60_node2.c
 *
 * Created: 27.10.2016 14:14:48
 *  Author: Whiskey Dicks 8===D
 */ 

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>		//This is also included in UART_driver.h. Should we remove it from here?
#include <util/delay.h>
#include <stdio.h>

#include "bit_macros.h"
#include "UART_driver.h"
#include "CAN.h"

int main(void) {
	
	// ------------ Set PB0 & PB7 to output ------------
	
	set_bit(DDRB, PB0);
	set_bit(DDRB, PB7);
	
	// ------------------------------------------------
	
	unsigned long clock_speed = F_CPU;
	
	UART_init(clock_speed);
	
	
	printf("before");
	
	can_init(MODE_LOOPBACK);
	
	printf("after");
	/*
	can_message test;
	test.id		= 1337;
	test.data[0]	= 'H';
	test.data[1]	= 'e';
	test.data[2]	= 'l';
	test.data[3]	= 'l';
	test.data[4]	= 'o';
	test.length	= 5;
	
	can_message test2;
	test2.id		= 1338;
	test2.data[0]	= 'W';
	test2.data[1]	= 'o';
	test2.data[2]	= 'r';
	test2.data[3]	= 'l';
	test2.data[4]	= 'd';
	test2.length	= 5;
	
	can_message_send(&test);
	
	
	while(1){
		
		can_message_send(&test2);
		
		if ( can_interrupt()){
			can_handle_messages();
		}
		
		_delay_ms(30);
	}
	*/
}