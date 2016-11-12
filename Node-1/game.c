/*
 * game.c
 *
 * Created: 12.11.2016 11:09:51
 *  Author: whiskey dick
 */ 

#define F_CPU 4915200UL

#include <avr/delay.h>

#include "joystick_driver.h"
#include "CAN.h"

void game_play(){
	can_message joy_pos;
	joystick_position_t position;
	
	uint8_t id = 0;
	uint8_t shoot = 0;
	printf("\t\t*----NODE 1 BOOTED----*\n\n");
	while(1){
		shoot = joystick_button(LBUTTON);
		position = joystick_get_position();
		joy_pos.data[0] = position.x;
		joy_pos.data[1] = position.y;
		joy_pos.data[2] = shoot;
		joy_pos.length = 3;
		joy_pos.id = id;
		
		can_message_send(&joy_pos);
		
		id = id + 1;
		_delay_ms(30);
	}
}