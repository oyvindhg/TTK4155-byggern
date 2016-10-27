
#include <stdint.h>
#include <stdio.h>
#include <stdarg.h>

#include "OLED_driver.h"
#include "font_4x6.h"
#include "font_5x7.h"
#include "font_5x7w.h"
#include "font_8x8.h"

static FILE mystdout = FDEV_SETUP_STREAM(oled_put_char, NULL, _FDEV_SETUP_WRITE);
static FILE myinvstdout = FDEV_SETUP_STREAM(oled_inv_put_char, NULL, _FDEV_SETUP_WRITE);

#ifndef OLED_COMMAND_ADDRESS
#define OLED_COMMAND_ADDRESS  0x1000
#endif

#ifndef OLED_DATA_ADDRESS
#define OLED_DATA_ADDRESS 0x1200
#endif

typedef enum{HORIZONTAL_MODE, VERTICAL_MODE, PAGE_MODE} adressing_mode;

volatile char* ext_oled_cmd = OLED_COMMAND_ADDRESS;
volatile char* ext_oled_data = OLED_DATA_ADDRESS;

volatile oled_position_t position;

volatile int fontSize = 8;
const char* const font[] PROGMEM = {font_4x6, font_5x7, font_5x7w, font_8x8};
int current_font = FONT_8X8;

void oled_is_out_of_bounds() {
	if (position.col > 127) {
		position.col -= 128;
		position.row += 1;
		if (position.row > 7) {
			position.row = 0;
		}
	}
}

void switch_font(fontName name) {
	current_font = name;
	switch(name){
		case(FONT_4X6):
			fontSize = 4;
		case(FONT_5X7):
			fontSize = 5;
		case(FONT_5X7W):
			fontSize = 5;
		case(FONT_8X8):
			fontSize = 8;
	}
}

void write_command(uint8_t command){
	ext_oled_cmd[0] = command;
}

void write_data(uint8_t data){
	ext_oled_data[0] = data;
}

int oled_put_char(unsigned char c){
	uint8_t printChar = c-32;
	
	for (int i=0; i < fontSize; i++) {
		write_data(pgm_read_word(&font_8x8[printChar][i]));
		position.col += fontSize;
		oled_is_out_of_bounds();
	}
	
	return 0;
}

int oled_inv_put_char(unsigned char c){
	uint8_t printChar = c-32;
	
	for (int i=0; i < fontSize; i++) {
		write_data(~pgm_read_word(&font_8x8[printChar][i]));
		position.col += fontSize;
		oled_is_out_of_bounds();
	}
	
	return 0;
}

void oled_set_adressing_mode(adressing_mode mode) {
	write_command(0x20);
	write_command(mode);
}

// ------------------ functions declared in header below this line---------------------

void oled_printf(char* data, ...){
	va_list args;
	va_start(args, data);
	vfprintf(&mystdout, data, args);
	va_end(args);
	
}

void oled_inv_printf(char* data, ...){
	va_list args;
	va_start(args, data);
	vfprintf(&myinvstdout, data, args);
	va_end(args);
	
}

//void oled_line_print(char* data){
	//printf("data: %s\n", data);
	//if (position.col + strlen(data)*fontSize > 127){
		//printf("data2: %s\n", data);
		////printf("ITS HERE: %d", position.col + strlen("Highscore"));
		//char newString[strlen(data)*fontSize];
		//sprintf(newString, "%s", data);
		//printf("newString: %s\n", newString);
		//printf("data4: \n");
		////oled_inv_printf(newString);
		////printf(newString);
	//}
	//else{
		//oled_printf(data);
	//}
//}
//
//void oled_inv_line_print(char* data){
	//if (position.col + strlen(data)*fontSize > 127){
		//char* newString;
		//sprintf(newString, data, 127/fontSize);
		//oled_inv_printf(newString);
	//}
	//else{
		//oled_inv_printf(data);
	//}
//}

int long_string(char* data){
	if (strlen(data)*fontSize > 128){
		return 1;
	}
	return 0;
}

void oled_align_centre(char* title) {
	oled_goto_column(64- fontSize*strlen(title)/2);
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
	
	//int line = 0;
	
	//printf("\nLINE: %d\n", line);
	
	for (int line = 0; line < 8; line++) {
		//printf("\nline: %d", line);
		oled_clear_line(line);
	}
	oled_home();
}

void oled_home(){
	oled_pos(0,0);
}

void oled_goto_line(int line){
	if (line > 7 || line < 0) {
		return 0;
	}
	else {
		position.row = line;
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
		position.col = column;
		oled_set_adressing_mode(PAGE_MODE);
		
		int numLow = column % 16;
		int numHigh = column / 16;
		
		write_command(numLow);
		write_command(16 + numHigh);
		oled_set_adressing_mode(HORIZONTAL_MODE);
	}
	
}

void oled_goto_letter(int letterPlace){
	if (letterPlace <= 0) {
		oled_goto_column(0);
	}
	else {
		oled_goto_column(letterPlace*fontSize-1);
	}
}

void oled_clear_line(int line){
	oled_pos(line, 0);
	
	for (int col = 0; col < 128; col++) {
		write_data(0b00000000);
	}
	oled_goto_line(line);	// siden horizontal mode
}

void oled_fill_line(int line){
	oled_pos(line,0);
	
	for (int col =0; col < 128; col++) {
		write_data(~0b00000000);
	}
	oled_goto_line(line);
}

void oled_pos(int row, int column){
	oled_goto_line(row);
	oled_goto_column(column);	
}