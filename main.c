/*
 * main.c
 *
 * Created: 03.09.2016 12:26:04
 *  Author: Whiskey dicks
 
 Crystal oscillator frequency: 4.9152 MHz

 Tip for debug of a variable: Use volatile when initializing the variable, then press Start Debugging and Break. Then add the variable to the watch-list after right clicking it. Now it can be viewed in debug mode.
 

SPØRSMÅL:

Decoupling capacitors. Er de blå ok?

Low-pass filter on ALE signal. Schematic on STK501???

SRAM capacitors page?


*/ 

#ifndef F_CPU
#define F_CPU 4915200UL	//This is just a macro, it has no data type.
#endif

#include <avr/io.h>		//This is also included in UART_driver.h. Should we remove it from here?
#include <util/delay.h>
#include <stdio.h>

#include "bit_macros.h"
#include "UART_driver.h"
#include "XMEM.h"
#include "SRAM_driver.h"
#include "ADC_driver.h"
#include "joystick_driver.h"
#include "OLED_driver.h"
#include "OLED_menu.h"
#include "CAN_controller_driver.h"
#include "CAN.h"


void exercise1(void) {
	
	//UART
	
	put_char(get_char() + 1);		//Returns the character next in the alphabet.

	printf("\nhello world!\n");
	
}

void exercise2(void) {
	
	//SRAM
	
	char data = 'c';
	
	volatile char* ext_ram = 0x1000;
	
	SRAM_test();

	while(1) {
		ext_ram[0x000] = data;
		//printf("OLED command\n");
		_delay_ms(3000);
		ext_ram[0x300] = data;
		//printf("OLED data\n");
		_delay_ms(3000);
		ext_ram[0x400] = data;
		//printf("ADC\n");
		_delay_ms(3000);
		ext_ram[0x800] = data;
		//printf("SRAM\n");
		_delay_ms(3000);
	}
	
}

void exercise3(void) {
	
	//Joystick
	
	joystick_position_t position;
	
	while(1){
		position = joystick_get_position();
		
		printf("Joystick: \tx: %d \t\tSlider:\tleft: %d \n", position.x, slider_get_left());
		printf("\t\ty: %d \t\t\tright: %d \n\n", position.y, slider_get_right());
		
		
		if (joystick_button(JOYSTICKBUTTON)){
			printf("JOYSTICK BUTTON\n");
		}
		
		if (joystick_button(LBUTTON)){
			printf("LEFT BUTTON\n");
		}
		
		if (joystick_button(RBUTTON)){
			printf("RIGHT BUTTON\n");
		}
		
		printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n\n");
		
		//_delay_ms(1000);
	};
}

void exercise4(void) {
	
	//OLED
	
	while(1){
		oled_menu_selection();
		_delay_ms(200);
	}
	
}

int main(void) {
	
	// -------------Define variables-------------
	
	int prescaler_joystick_timer = 1024;	//Only this? Is it necessary?
	
	// ------------------------------------------

	unsigned long clock_speed = F_CPU;
	
	UART_init(clock_speed);
	XMEM_init();
	
	ADC_init();
	
	joystick_init(prescaler_joystick_timer);
	
	oled_init();
	
	oled_menu_init();
	
	printf("wtf is real");
	
	can_init();
	
	can_message test;
	test.id		= 729;
	test.data[0]	= 'h';
	test.data[1]	= 'e';
	test.data[2]	= 'l';
	test.data[3]	= 'l';
	test.length	= 4;
	
	//can_message_send(&test);
	
	printf("BRA\n");
	_delay_ms(3000);
	printf("3sec");
	
	while(1){
		if ( can_interrupt()){
			printf("\n!\n");
			//can_handle_messages();
		}
		_delay_ms(30);
	}
	
	return 0;
}