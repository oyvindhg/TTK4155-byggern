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
#include "joystick_driver.h"

#include <stdio.h>

int currentLine = 2;

volatile menu_t *current_menu;

int oled_menu_selection() {
	joystick_direction_t direction = joystick_get_direction();
	if (direction == UP) {
		currentLine--;
		if (currentLine < 2) {
			currentLine = 6;
		}
		return 1;
	}else if (direction == DOWN) {
		currentLine++;
		if (currentLine > 6) {
			currentLine = 2;
		}
		return 1;
	} else {
		return 0;
	}
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

menu_t *oled_menu_init(void) {
	menu_t* main_menu = new_menu("Main Menu", NULL);
	menu_t* highscores = new_menu("Highscores", main_menu);
	menu_t* play_game = new_menu("Play Game", main_menu);
	menu_t* calibrate_joystick = new_menu("Calibrate", main_menu);
	menu_t* set_difficulty = new_menu("Set Difficulty", main_menu);
	menu_t* debugging = new_menu("Debugging", main_menu);
	menu_t* highscore_1 = new_menu("1. PAK ER BEST", highscores);
	menu_t* highscore_2 = new_menu("2. O(lol) BAD", highscores);
/*
	menu_t* highscore_1 = (menu_t*) malloc(sizeof(menu_t*));
		highscore_1->title = "PAK BEST";
		highscore_1->parent = highscores;
		//highscore_1.items = (char*) malloc(sizeof(char*));
		//check_memory(highscore_1.items);
		//highscore_1.items[0] = "9999";  
		highscore_1->first_child = NULL;
		
		highscore_1->items = NULL;
	
	menu_t* highscore_2 = (menu_t*) malloc(sizeof(menu_t*));
		highscore_2->title = "O(lol) worst";
		highscore_2->parent = highscores;
		//highscore_2.items = (char*) malloc(sizeof(char*));
		//check_memory(highscore_2.items);
		//highscore_2.items[0] = "7";
		highscore_2->first_child = NULL;
		highscore_2->right_sibling = NULL;
		
		highscore_2->items = NULL;
*/	

	main_menu->first_child = highscores;
	set_right_sibling(highscores, play_game);
	set_right_sibling(play_game, calibrate_joystick);
	set_right_sibling(calibrate_joystick, set_difficulty);
	set_right_sibling(set_difficulty, debugging);
	
	highscores->first_child = highscore_1;
	set_right_sibling(highscore_1, highscore_2);
	
	current_menu = main_menu;
	return current_menu;
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
	oled_reset();
	printTitle(menu->title);
	int line = 2;
	menu = menu->first_child;
	
	while (menu != NULL && line < 8) {
		//printf("lol");
		oled_pos(line,0);
		if (currentLine == line) {
			oled_fill_line(line);
			oled_inv_printf(menu->title);
		}else {
			oled_printf(menu->title);
		}
		++line;
		menu = menu->right_sibling;
	}
	
}