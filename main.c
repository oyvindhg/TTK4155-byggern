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

#include <avr/io.h>
#include <util/delay.h>

#include "bit_macros.h"
#include "UART_driver.h"

//#define DDRB |= (1 << PB1)		// Data direction register B. 1 sets port PB1 to output mode.
//Funker dette? Ser ikke forskjell

void day1(void) {
	
	put_char(get_char() + 1);		//Returns the character next in the alphabet.

	printf("hello world!\n");
	
}

void day2(void) {

	
}

int main(void) {

	unsigned long clock_speed = F_CPU;
	UART_init(clock_speed);
	
	//DDRA = 0xFF;			//Er dette nødvendig når vi enabler etterpå? Vil ikke dette bli overskrevet (ref. datablad) når vi enabler nedenfor? NEI

	set_bit(MCUCR,SRE);		//Enable External Memory Interface. PE1 is automatically controlled as this command takes control.
	set_bit(SFIOR,XMM2);	//Remove 4 Most Significant Bits from address so that JTAG interface doesn't crash

	volatile char* ext_ram = 0x1800;	//Create a pointer to the array of all addresses we will write to. SRAM starting at 0x1800. ext_ram[0x7FF] is maximum because 0x1800 + 0x7FF = 0x1FFF! 
	
	while(1) {
		ext_ram[0x05] = 0xFF;		//Set data 0xFF to address 0x05. Each address points to a 8-bit register.
		_delay_ms(200);
		ext_ram[0x01] = 0x00;
		_delay_ms(200);
	}
	
	return 0;
}