/*
 * game.c
 *
 * Created: 12.11.2016 11:18:40
 *  Author: whiskey dick
 */ 

#define F_CPU 16000000UL

#include <avr/delay.h>

#include "CAN.h"
#include "servo_driver.h"
#include "motor_driver.h"
#include "solenoid_driver.h"
#include "PID.h"
#include "UART_node_3.h"

void game_play() {
	int8_t motor_pos = 0;
	int8_t servo_pos = 0;
	uint8_t shoot = 0;
	can_message joy_data;
	uint8_t motor_flag = 0;
	
	int16_t rot = 0;
	uint8_t power = 80;
	int16_t motor_ref;
	int16_t motor_rot;
	int16_t motor_diff;
	uint8_t score = 0;
	uint8_t reverse_servo = 0;
	difficulty_t diff = MEDIUM;
	uint8_t started = 0;
	uint8_t music;
	
	printf("\t\t*----NODE 2 BOOTED----*\n\n");
	while(1) {
		if (can_interrupt()){
			joy_data = can_handle_messages();
			
			if (joy_data.id == DIFFICULTY){
				diff = joy_data.data[0];
				PID_update(diff);
				if (diff != HARD){
					reverse_servo = 0;
				}
				continue;
			}
			
			if (joy_data.id == SONG) {
				music = joy_data.data[0];
				put_char_3(music);
				
			}
			motor_pos = joy_data.data[0];
			PID_update_pos_ref(motor_pos);
			servo_pos = joy_data.data[1];
			shoot = joy_data.data[2];
			if (shoot) {
				solenoid_shoot();
				started = 1;
				score = score + 1;
				if (diff == HARD){
					reverse_servo = !reverse_servo;
				}
			}
			if (reverse_servo){
				servo_pos = -servo_pos;
			}
			set_servo(servo_pos);
		}
 		if (IR_game_over() && !shoot && started){
			//printf("score: %d", score);
			put_char_3(0);
			can_message game_over;
			game_over.id = 0;
			game_over.length = 1;
			game_over.data[0] = score;
			can_message_send(&game_over);
			started = 0;
 		}
	}
	
}
