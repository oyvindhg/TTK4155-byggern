/*
 * Byggern_gr60_node2.c
 *
 * Created: 27.10.2016 14:14:48
 *  Author: Whiskey Dicks
 */ 

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>	
#include <util/delay.h>
#include <stdio.h>

#include "bit_macros.h"
#include "UART_driver.h"
#include "UART_node_3.h"
#include "CAN.h"
#include "servo_driver.h"
#include "IR_driver.h"
#include "DAC_driver.h"
#include "motor_driver.h"
#include "solenoid_driver.h"
#include "game.h"
#include "UART_node_3.h"

void exercise_6() {

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
	can_message_send(&test2);
	
	uint8_t id = 0;
	while(1){
		id = id + 1;
		test.id = id;
		can_message_send(&test);
		printf("ID: %d\n", test.id);
		printf("Message: ");
		for (int i = 0; i < test.length; i++) {
			printf("%c", test.data[i]);
		}
		printf("\n");
		id = id + 1;
		test2.id = id;
		
		_delay_ms(30);
		
		printf("ID: %d\n", test2.id);
		printf("Message: ");
		can_message_send(&test2);
		for (int i = 0; i < test2.length; i++) {
			printf("%c", test2.data[i]);
		}
		printf("\n\n");
		if ( can_interrupt()){
			can_handle_messages();
		}
		
		_delay_ms(30);
		
	}
}


int main(void) {
	
	unsigned long clock_speed = F_CPU;
	UART_init(clock_speed);
	UART_init_3(clock_speed);
	
	DAC_init();
	
	motor_init();
	
	PID_init();
	
	can_init(MODE_NORMAL);
	
	servo_init(clock_speed);
	
	IR_init();
	
	solenoid_init();
	
	game_play();
}