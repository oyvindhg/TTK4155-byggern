
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
	
	int fontSize = 8;
	for (int i=0; i < fontSize; i++) {
		write_data(pgm_read_word(&font[printChar][i]));
		
	}
	
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
	write_command(0xa1); //segment remap	/A0 flips text horizontally
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
	
	oled_set_adressing_mode(HORIZONTAL_MODE);
	
	write_command(0xdb); //VCOM deselect level mode
	write_command(0x30);
	write_command(0xad); //master configuration
	write_command(0x00);
	write_command(0xa4); //out follows RAM content
	write_command(0xa6); //set normal display
	write_command(0xaf); // display on
	oled_reset();
	
}

void oled_reset(){
	
	for (int row = 0; row < 8; row++) {
		for (int col = 0; col < 128; col++) {
			write_data(0x00000000);
		}
	}
	
	oled_home();
}

void oled_set_adressing_mode(adressing_mode mode) {
	write_command(0x20);
	write_command(mode);
}

void oled_home(){
	oled_goto_line(0);
	oled_goto_column(0);
}

void oled_goto_line(int line){
	if (line > 7 || line < 0) {
		return 0;
	} 
	else {
		oled_set_adressing_mode(PAGE_MODE);
		write_command(0xB0 + line);
		oled_set_adressing_mode(HORIZONTAL_MODE);
	}
}

void oled_goto_column(int column){
	if (column > 127 || column < 0) {
		return 0;
	} 
	else {
		oled_set_adressing_mode(PAGE_MODE);
		
		int numLow = column % 16;
		int numHigh = column / 16;
		
		write_command(numLow);
		write_command(16 + numHigh);
		oled_set_adressing_mode(HORIZONTAL_MODE);
	}
	
}

void oled_clear_line(int line){
	oled_goto_line(line);
	oled_goto_column(0);
	
	for (int col = 0; col < 128; col++) {
		write_data(0x00000000);
	}
	oled_goto_line(line);	// siden horizontal mode
}

void oled_pos(int row, int column){
	
}