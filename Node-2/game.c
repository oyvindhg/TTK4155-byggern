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

void game_play() {
	int8_t motor_pos = 0;
	int8_t servo_pos = 0;
	uint8_t shoot = 0;
	uint8_t goals = 0;
	can_message joy_data;
	uint8_t motor_flag = 0;
	
	int16_t rot = 0;
	uint8_t power = 70;
	uint8_t counter = 4;
	int16_t motor_ref;
	int16_t motor_rot;
	int16_t motor_diff;
	//IR_goal_counter(0);
	
	printf("\t\t*----NODE 2 BOOTED----*\n\n");
	while(1) {
		if (can_interrupt()){
			joy_data = can_handle_messages();
			motor_pos = joy_data.data[0];
			motor_ref = (int16_t)(motor_pos*(-40)) - 4250;
			motor_rot = motor_read_rotation(0);
			motor_diff = -motor_ref + motor_rot;
// 			printf("REF: %d\n", motor_ref);
// 			printf("CUR: %d\n", motor_rot);
			printf("\t\t DIFF: %d\n", motor_diff);
			servo_pos = joy_data.data[1];
			shoot = joy_data.data[2];
			if (shoot) {
				counter = counter+1;
			}
		}
// 		motor_ref = (int16_t)(motor_pos*(-40)) - 4250;
// 		motor_rot = motor_read_rotation(0);
		//motor_move(motor_diff, power);
		if ((motor_diff >100) && motor_flag!=1) {
			motor_set_direction(RIGHT);
			motor_set_speed(power);
			motor_flag = 1;
		}
		else if (motor_diff <-100 && motor_flag!=2) {
			motor_set_direction(LEFT);
			motor_set_speed(power);
			motor_flag = 2;
		}
		else if (abs(motor_diff) < 100 && (motor_flag!=0)){
			motor_set_speed(0);
			motor_flag = 0;
		}
		
		set_servo(servo_pos);
		
		if (shoot==4 && (counter>4)) {
			solenoid_shoot();
			counter = 0;
		}
		//IR_goal_counter(1);
	}
	
}