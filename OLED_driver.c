
#include <stdint.h>
#include <stdio.h>
#include <stdarg.h>

#include "OLED_driver.h"
#include "font_8x8.h"

static FILE mystdout = FDEV_SETUP_STREAM(oled_put_char, NULL, _FDEV_SETUP_WRITE);

#ifndef OLED_COMMAND_ADDRESS
#define OLED_COMMAND_ADDRESS  0x1000
#endif

#ifndef OLED_DATA_ADDRESS
#define OLED_DATA_ADDRESS 0x1200
#endif

volatile char* ext_oled_cmd = OLED_COMMAND_ADDRESS;
volatile char* ext_oled_data = OLED_DATA_ADDRESS;


void write_command(uint8_t command){
	ext_oled_cmd[0] = command;
}

void write_data(uint8_t data){
	ext_oled_data[0] = data;
}

int oled_put_char(unsigned char c){
	uint8_t printChar = c-32;
	for (int i=0; i < 8; i++) {
		//write_data(font[printChar][i]);
		//write_data(0b01011111);
		write_data(*font[3] + i);
		
	}
	
	printf("what: %d", font[1][1]);
	
	write_data(0b00000000);
	write_data(0b00000110);
	write_data(0b01011111);
	write_data(0b01011111);
	write_data(0b00000110);
	write_data(0b00000000);
	write_data(0b00000000);
	
	return 0;
}

void oled_printf(char* data, ...){
	va_list args;
	va_start(args, data);
	vfprintf(&mystdout, data, args);
	va_end(args);
	
}


void oled_init(){
	write_command(0xae); // display off
	write_command(0xa1); //segment remap
	write_command(0xda); //common pads hardware: alternative
	write_command(0x12);
	write_command(0xc8); //common output scan direction:com63~com0
	write_command(0xa8); //multiplex ration mode:63
	write_command(0x3f);
	write_command(0xd5); //display divide ratio/osc. freq. mode
	write_command(0x80);
	write_command(0x81); //contrast control
	write_command(0x50);
	write_command(0xd9); //set pre-charge period
	write_command(0x21);
	
	write_command(0x20); //Set Memory Addressing Mode
	write_command(0x00);		// Set to horizontal addressing mode! 0x01 is vertical. 0x02 is Page.
	
	write_command(0xdb); //VCOM deselect level mode
	write_command(0x30);
	write_command(0xad); //master configuration
	write_command(0x00);
	write_command(0xa4); //out follows RAM content
	write_command(0xa6); //set normal display
	write_command(0xaf); // display on
}

void oled_reset(){
	
}

void oled_home(){
	
}

void oleg_goto_line(line){
	
}

void oled_goto_column(column){
	
}

void oled_clear_line(line){
	
}

void oled_pos(row, column){
	
}