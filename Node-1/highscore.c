/*
 * highscore.c
 *
 * Created: 19.11.2016 17:19:56
 *  Author: WD
 */
 
#ifndef F_CPU
#define F_CPU 4915200UL	//This is just a macro, it has no data type.
#endif

#include <stdio.h>
#include <avr/delay.h>

#include "highscore.h"
#include "OLED_driver.h"
#include "joystick_driver.h"

void highscore_write(){
	for (int i = 2; i <=6 ; i++){
		oled_clear_line(i);
	}
	
	oled_pos(3,0);
	oled_printf("Name: ");
	
	char name[4] = "   \0";
	
	int8_t first = 1;
	int8_t count = 0;
	int8_t blink = 0;
	
	char next_char = 'X';
	oled_goto_letter(6);
	oled_inv_put_char(next_char);
	
	while (1){
		
		if (joystick_button(RBUTTON)){
			if (first){
				name[0] = 'X';
			}
			break;
		}
		else if (joystick_button(LBUTTON)){
			if (count == 2){
				name[count] = next_char;
				break;
			}
			first = 0;
			oled_goto_letter(6 + count);
			oled_put_char(next_char);
			name[count] = next_char;
			count = count + 1;
		}
		else if (joystick_get_direction() == DOWN){
			oled_goto_letter(6 + count);
			next_char += 1;
			if (next_char > 'Z'){
				next_char = 'A';
			}
		}
		else if (joystick_get_direction() == UP){
			oled_goto_letter(6 + count);
			next_char -= 1;
			if (next_char < 'A'){
				next_char = 'Z';
			}
			
		}
		
		_delay_ms(150);
		blink += 1;
		if (blink == 3){
			blink = 0;
			oled_goto_letter(6 + count);
			oled_put_char(' ');
		}
		else{
			oled_goto_letter(6 + count);
			oled_inv_put_char(next_char);
		}
		
	}
	
	printf(name);
	_delay_ms(2000);
	
}