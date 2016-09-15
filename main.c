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

#include "bit_macros.h"
#include "UART_driver.h"
#include "XMEM.h"
#include "SRAM_driver.h"

//#define DDRB |= (1 << PB1)		// Data direction register B. 1 sets port PB1 to output mode.
//Funker dette? Ser ikke forskjell


void exercise1(void) {
	
	put_char(get_char() + 1);		//Returns the character next in the alphabet.

	printf("hello world!\n");
	
}


void exercise2(void) {

	
}

int main(void) {
	
	
	char data = 'c';
	volatile char* ext_ram = 0x1000;

	unsigned long clock_speed = F_CPU;
	
	UART_init(clock_speed);
	XMEM_init();
	
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
	
	return 0;
}