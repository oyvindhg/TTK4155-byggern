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
#include "EEPROM.h"

	
highscore first;
highscore second;
highscore third;
highscore new_score;


void read_score(highscore* hs, int8_t mem_loc){
	
	for (int i = 0; i < 3; i++){
		hs->name[i] = EEPROM_read(mem_loc+i);
	}
	
	hs->score = EEPROM_read(mem_loc+3);
}

void write_score(highscore hs, int8_t mem_loc){
	for (int i = 0; i < 3; i++){
		EEPROM_write(mem_loc+i, hs.name[i]);
	}
	EEPROM_write(mem_loc+3, hs.score);
}

void highscore_init(){
	
	read_score(&first, 0);
	
	read_score(&second, 4);

 	read_score(&third, 8);
	
	
}

void print_highscore(){
	for (int i = 2; i <=6 ; i++){
		oled_clear_line(i);
	}
	oled_pos(3,0);
	oled_printf("1: ");
	for (uint8_t i = 0; i < 3; i++) {
		oled_printf("%c", first.name[i]);
	}
	oled_printf(" - %d", first.score);
	
	oled_pos(4,0);
	oled_printf("2: ");
	for (uint8_t i = 0; i < 3; i++) {
		oled_printf("%c", second.name[i]);
	}
	oled_printf(" - %d", second.score);
	
	oled_pos(5,0);
	oled_printf("3: ");
	for (uint8_t i = 0; i < 3; i++) {
		oled_printf("%c", third.name[i]);
	}
	oled_printf(" - %d", third.score);
}

void score_copy(highscore* a, highscore* b){
	a->name[0] = b->name[0];
	a->name[1] = b->name[1];
	a->name[2] = b->name[2];
	a->score = b->score;
}


void insert_score(char* name, uint8_t score){
	
	
	for (uint8_t i = 0; i < 3; i++){
		new_score.name[i] = name[i];
	}
	new_score.score = score;
	
	if (new_score.score >= first.score){
		score_copy(&third, &second);
		score_copy(&second, &first);
		score_copy(&first, &new_score);
		write_score(first, 0);
		write_score(second, 4);
		write_score(third, 8);
	}
	else if (new_score.score >= second.score){
		score_copy(&third, &second);
		score_copy(&second, &new_score);
		write_score(second, 4);
		write_score(third, 8);
	}
	else if (new_score.score >= third.score){
		score_copy(&third, &new_score);
		write_score(third, 8);
	}
	
}

uint8_t check_score(uint8_t score){
	if (score >= third.score){
		return 1;
	}
	return 0;
}

void create_nickname(char* name){
	
	
	for (int i = 2; i <=6 ; i++){
		oled_clear_line(i);
	}
	
	oled_pos(3,0);
	oled_printf("Name: ");
	
	int8_t first = 1;
	int8_t count = 0;
	int8_t blink = 0;
	
	char next_char = 'X';
	oled_goto_letter(6);
	oled_inv_put_char(next_char);
	
	while (1){
		
		if (joystick_button(LBUTTON)){
			if (first){
				name[0] = 'X';
			}
			break;
		}
		else if (joystick_button(RBUTTON)){
			if (count == 2){
				name[count] = next_char;
				break;
			}
			first = 0;
			oled_goto_letter(6 + count);
			oled_put_char(next_char);
			name[count] = next_char;
			count = count + 1;
			_delay_ms(300);
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

}
