/*
 * OLED_menu.c
 *
 * Created: 06.10.2016 11:15:02
 *  Author: Whiskey Dicks
 */ 

//(menu_t*) malloc(sizeof(menu_t*));
//malloc(sizeof(menu_t));

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
	menu->items = NULL;
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
	menu_t* debugging = new_menu("Debug", main_menu);
	menu_t* poem = new_menu("Read poem", main_menu);
	menu_t* watch_art = new_menu("Watch pixel art", main_menu);
	
	menu_t* highscore_1 = new_menu("PAK", highscores);
	
	menu_t* auto_calibrate = new_menu("Auto-calibrate", calibrate_joystick);
	menu_t* manual_calibrate = new_menu("Manual calibration", calibrate_joystick);
	
	menu_t* easy = new_menu("Kinder garden", set_difficulty);
	menu_t* medium = new_menu("Acceptable", set_difficulty);
	menu_t* hard = new_menu("Wrist breaker", set_difficulty);
	
	menu_t* byggern_poem = new_menu("Roses are red, violets are blue. Byggern is hard and so am I.", poem);

	
	set_first_child(main_menu, highscores);
	set_right_sibling(highscores, play_game);
	set_right_sibling(play_game, calibrate_joystick);
	set_right_sibling(calibrate_joystick, set_difficulty);
	set_right_sibling(set_difficulty, debugging);
	set_right_sibling(debugging, poem);
	set_right_sibling(poem, watch_art);
	
	set_first_child(highscores, highscore_1);
	
	set_first_child(calibrate_joystick, auto_calibrate);
	set_right_sibling(auto_calibrate, manual_calibrate);
	
	set_first_child(set_difficulty, easy);
	set_right_sibling(easy, medium);
	set_right_sibling(medium, hard);
	
	set_first_child(poem, byggern_poem);
	
	current_menu = main_menu;
	current_menu_size = size_of_menu(current_menu);
	oled_menu_print(current_menu);
	return current_menu;
}

void oled_menu_selection() {
	
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
	}
	else {
		if (joystick_button(RBUTTON)) {
			goto_menu(RBUTTON);
		}
		if (joystick_button(LBUTTON)) {
			goto_menu(LBUTTON);
		}
		if (cutter != 0 || title_cutter != 0){
			oled_menu_print(current_menu);
			}
		return;
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

	if (selected_menu == NULL || selected_menu->first_child == NULL) {
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
	menu_size ++;											//Riktigere enn int menu_size = 1; ?
	while (menu->right_sibling != NULL) {
		menu = menu->right_sibling;							//Vil ikke current menu nå peke til siste barnet??? :S
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
			//printf("Current\n");
			
			oled_fill_line(line);
			
			if (cutter == -1){
				cutter ++;
			}
			
			if (long_string(menu->title + cutter)){
				//printf("%d\n", strlen(menu->title + cutter));
				//printf("cutter: %d", cutter);
				//char* line;
				//sprintf(line, "%s", menu->title + cutter);
				
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
			//printf("Not current\n");
			//printf("%s", menu->title);
			oled_printf(menu->title);
		}
		++line;
		menu = menu->right_sibling;
	}
	
}