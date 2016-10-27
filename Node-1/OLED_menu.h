/*
 * OLED_menu.h
 *
 * Created: 06.10.2016 11:15:16
 *  Author: perakj
 */ 


#ifndef OLED_MENU_H_
#define OLED_MENU_H_

#include "joystick_driver.h"

typedef struct{
	char* title;
	char** items;
	//pikks or it didn't happen
	struct menu_t* parent;
	struct menu_t* first_child;
	struct menu_t* right_sibling;
} menu_t;

void oled_menu_selection(void);
menu_t *oled_menu_init(void);
void oled_menu_print(menu_t *menu);
void goto_menu(usb_button_t button);

#endif /* OLED_MENU_H_ */