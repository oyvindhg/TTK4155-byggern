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

uint8_t game_play(){
	can_message joy_pos;
	joystick_position_t position;
	int slider_r;
	
	uint8_t shoot = 0;
	uint8_t prev_shoot = 0;
	can_message score;

	while(1){
		
		if(can_interrupt() || joystick_button(JOYSTICKBUTTON)){
			score = can_handle_messages();
			printf("Score: %d", score.data[0]);
			return score.data[0];
		}
		
		shoot = joystick_button(RBUTTON);
		//printf("%d", shoot);
		if (prev_shoot == 1 && shoot == 0) {
			prev_shoot = 0;
		}
		position = joystick_get_position();
		joy_pos.data[1] = -position.x;
		
		slider_r = slider_get_right();
		joy_pos.data[0] = slider_r;
		
		if (shoot && prev_shoot!=1) {
			prev_shoot = 1;
		}
		else {
			shoot = 0;
		}
		
		//printf("Sent: %d \n", shoot);
		joy_pos.data[2] = shoot;
		joy_pos.length = 3;
		joy_pos.id = GAME;
		
		can_message_send(&joy_pos);
		
		_delay_ms(70);
		
	}
}

void send_difficulty(uint8_t difficulty){
	can_message message;
	message.id = DIFFICULTY;
	message.length = 1;
	message.data[0] = difficulty;
	can_message_send(&message);
}