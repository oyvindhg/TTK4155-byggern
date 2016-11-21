/*
 * OLED_menu.h
 *
 * Created: 06.10.2016 11:15:16
 *  Author: whiskey dick
 */ 


#ifndef OLED_MENU_H_
#define OLED_MENU_H_

#include "joystick_driver.h"

typedef struct{
	char* title;
	struct menu_t* parent;
	struct menu_t* first_child;
	struct menu_t* right_sibling;
} menu_t;

typedef enum{
	NONE,
	PLAY_GAME,
	GAME_OVER,
	SAVE_HIGHSCORE,
	HIGHSCORE,
	AUTO_CALIBRATE,
	EASY,
	MEDIUM,
	HARD,
	ZELDA,
	MARIO,
	UW
	} menu_option_t;

menu_option_t oled_menu_selection(void);
menu_t *oled_menu_init(void);
void oled_menu_print(menu_t *menu);
void goto_menu(usb_button_t button);
void oled_print_status(menu_option_t);

#endif /* OLED_MENU_H_ */