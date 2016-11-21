/*
 * OLED_menu.c
 *
 * Created: 06.10.2016 11:15:02
 *  Author: Whiskey Dicks
 */ 

#include "OLED_driver.h"
#include "OLED_menu.h"

#include <string.h>
#include <stdio.h>

volatile int current_line = 2;
volatile int current_menu_size;

volatile menu_t *current_menu;

int cutter = 0;
int title_cutter = 0;
int display_line_offset = 0;

menu_t* new_menu(char* name, menu_t* parent) {
	menu_t* menu = malloc(sizeof(menu_t));
	menu->title = name;
	menu->parent = parent;
	menu->right_sibling = NULL;
	menu->first_child = NULL;
	return menu;
}

void set_right_sibling(menu_t* menu, menu_t* right_sibling) {
	menu->right_sibling = right_sibling;
}

void set_first_child(menu_t* menu, menu_t* first_child) {
	menu->first_child = first_child;
}

menu_t *oled_menu_init(void) {
	menu_t* main_menu = new_menu("Main Menu", NULL);
	menu_t* highscores = new_menu("Highscores", main_menu);
	menu_t* play_game = new_menu("Play Game", main_menu);
	menu_t* calibrate_joystick = new_menu("Calibrate Joystick", main_menu);
	menu_t* set_difficulty = new_menu("Set Difficulty", main_menu);
	menu_t* poem = new_menu("Read poem", main_menu);
	menu_t* songs = new_menu("Melodies", main_menu);
	menu_t* extra = new_menu("Extras", main_menu);
	menu_t* mario = new_menu("Super Mario", songs);
	menu_t* mario2 = new_menu("Underworld", songs);
	menu_t* zelda = new_menu("Zelda", songs);
	
	menu_t* easy = new_menu("Kinder garden", set_difficulty);
	menu_t* medium = new_menu("Acceptable", set_difficulty);
	menu_t* hard = new_menu("Wrist breaker", set_difficulty);
	
	menu_t* byggern_poem = new_menu("Roses are red, violets are blue. Byggern is hard.", poem);

	
	set_first_child(main_menu, play_game);
	set_right_sibling(play_game, highscores);
	set_right_sibling(highscores, calibrate_joystick);
	set_right_sibling(calibrate_joystick, set_difficulty);
	set_right_sibling(set_difficulty, poem);
	set_right_sibling(poem, songs);
	set_right_sibling(songs, extra);
	
	set_first_child(songs, zelda);
	set_right_sibling(zelda, mario);
	set_right_sibling(mario, mario2);
	
	set_first_child(set_difficulty, easy);
	set_right_sibling(easy, medium);
	set_right_sibling(medium, hard);
	
	set_first_child(poem, byggern_poem);
	
	current_menu = main_menu;
	current_menu_size = size_of_menu(current_menu);
	oled_menu_print(current_menu);

	return current_menu;
}

menu_option_t oled_menu_selection() {
	
	joystick_direction_t direction = joystick_get_direction();
	
	if (direction == UP) {
		cutter = 0;
		title_cutter = 0;
		current_line--;
		if (current_line < 2) {
			current_line = current_line+current_menu_size;
			if (current_menu_size > 6){
				display_line_offset = current_menu_size - 5;
			}
		}
		if (current_line < display_line_offset + 2){
			display_line_offset --;
		}
		oled_menu_print(current_menu);
		return NONE;
	}
	else if (direction == DOWN) {
		cutter = 0;
		title_cutter = 0;
		current_line++;
		if (current_line >= 2 + current_menu_size) {
			current_line = 2;
			display_line_offset = 0;
		}
		if (current_line > 6){
			display_line_offset = current_line - 6;
		}
		oled_menu_print(current_menu);
		return NONE;
	}
	else {
		if (joystick_button(RBUTTON)) {
			goto_menu(RBUTTON);
			if (current_menu->title == "Play Game"){
				return PLAY_GAME;
				}
			else if (current_menu->title == "Highscores"){
				return HIGHSCORE;
			}
			else if (current_menu->title == "Calibrate Joystick"){
				return AUTO_CALIBRATE;
			}
			else if (current_menu->title == "Kinder garden"){
				return EASY;
			}
			else if (current_menu->title == "Acceptable"){
				return MEDIUM;
			}
			else if (current_menu->title == "Wrist breaker"){
				return HARD;
			}
			else if (current_menu->title == "Zelda"){
				return ZELDA;
			}
			else if (current_menu->title == "Super Mario"){
				return MARIO;
			}
			else if (current_menu->title == "Underworld"){
				return UW;
			}
		}
		if (joystick_button(LBUTTON)) {
			goto_menu(LBUTTON);
		}
		if (cutter != 0 || title_cutter != 0){
			oled_menu_print(current_menu);
			}
		return NONE;
	}
}

void goto_menu(usb_button_t button) {
	display_line_offset = 0;
	int i = 2;
	menu_t* selected_menu = current_menu;
	
	if (button == RBUTTON) {
		selected_menu = current_menu->first_child;
		for (i; i < current_line; i++) {
			selected_menu = selected_menu->right_sibling;
		}
	}
	else if (button == LBUTTON) {
		selected_menu = current_menu->parent;
	}

	if (selected_menu == NULL) {
		return;
	} else {
		current_menu = selected_menu;
		current_menu_size = size_of_menu(current_menu);
		current_line = 2;
		cutter = 0;
		title_cutter = 0;
		oled_menu_print(selected_menu);
		return;
	}
}

int size_of_menu(menu_t* menu) {
	
	int menu_size = 0;
	
	menu = menu->first_child;
	if (menu == NULL) {
		return menu_size;
	}
	menu_size ++;											
	while (menu->right_sibling != NULL) {
		menu = menu->right_sibling;		
		menu_size++;
	}
	return menu_size;	
}
	
void check_memory(ptr){
	if (ptr == NULL)
	{
		printf(" Out of memory!\n");
		exit(1);
	}
	else{
		printf("OK");
	}
}

void printTitle(char* title){
	oled_align_centre(title);
	int i = 0;
	while(title[i])
	{
		unsigned char c = toupper(title[i]);
		
		oled_put_char(c);
		i++;
	}
	oled_pos(1,0);
	for (int i = 0; i < 16; i++) {
		oled_printf("-");
	}
	oled_pos(2,0);
}

void oled_menu_print(menu_t *menu) {
	
	if (cutter < -1){
		cutter ++;
		return;
	}
	if (title_cutter < -1){
		title_cutter ++;
		return;
	}
	
	oled_reset();
	
	if (title_cutter == -1){
		title_cutter ++;
	}
	
	if (long_string(menu->title + title_cutter)){
		title_cutter ++;
		printTitle(menu->title + title_cutter);
	}
	
	else if(title_cutter > 0){
		printTitle(menu->title);
		title_cutter = -5;
		
	}
	else{
		printTitle(menu->title);
	}
	
	int line = 2;
	
	menu = menu->first_child;
	
	for (int i = 0; i < display_line_offset; i++){
		menu = menu->right_sibling;
	}
	
	
	while (menu != NULL && line < 7) {
		
		oled_pos(line,0);
		
		if (current_line == line + display_line_offset) {
			
			oled_fill_line(line);
			
			if (cutter == -1){
				cutter ++;
			}
			
			if (long_string(menu->title + cutter)){
				
				cutter ++;
				oled_inv_printf(menu->title + cutter);
			}
			
			else if(cutter > 0){
				oled_inv_printf(menu->title);
				cutter = -5;
			}
			else{
				oled_inv_printf(menu->title);
			}
		}else {
			oled_printf(menu->title);
		}
		++line;
		menu = menu->right_sibling;
	}
	
}

void oled_print_status(menu_option_t opt){
	
	for (int i = 2; i <=6 ; i++){
		oled_clear_line(i);
	}
	
	oled_pos(3,0);
	char* status;
	switch(opt){
		case PLAY_GAME:
			status = "HAVE FUN!";
			oled_align_centre(status);
			oled_printf(status);
			break;
		case GAME_OVER:
			status = "GAME OVER!";
			oled_align_centre(status);
			oled_printf(status);
			oled_pos(4,0);
			status = "PLAY AGAIN?";
			oled_align_centre(status);
			oled_printf(status);
			oled_pos(6,0);
			status = "NO     /     YES";
			oled_align_centre(status);
			oled_printf(status);
			break;
		case SAVE_HIGHSCORE:
			status = "SAVE HIGHSCORE?";
			oled_align_centre(status);
			oled_printf(status);
			oled_pos(6,0);
			status = "NO     /     YES";
			oled_align_centre(status);
			oled_printf(status);
			break;
		case HIGHSCORE:
			oled_pos(2,0);
			status = "HIGHSCORES:";
			oled_align_centre(status);
			oled_printf(status);
			break;
		case AUTO_CALIBRATE:
			status = "CALIBRATED!";
			oled_align_centre(status);
			oled_printf(status);
			break;
		case EASY:
		case MEDIUM:
		case HARD:
			status = "DIFFICULTY SET!";
			oled_align_centre(status);
			oled_printf(status);
			break;
	}
	
}