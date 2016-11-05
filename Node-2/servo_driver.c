/*
 * servo_driver.c
 *
 * Created: 03.11.2016 11:20:35
 *  Author: Whiskey Dicks
 */ 

#include "servo_driver.h"
#include "PWM_driver.h"
#include <avr/io.h>

void servo_init(unsigned long clock_speed){
	
	float period_sec = 0.02;
	
	uint16_t aaa = period_sec;
	
	//printf("REAL_sec: %.2f\n", period_sec);
	
	PWM_init(period_sec, clock_speed);
	
	PWM_pulse_set(0.0015);
	
}


void set_servo(int servo_dir){
	
	float min_pw = 0.0009;
	float max_pw = 0.0021;
	
	float dir = (float)servo_dir;
	
	float servo_pw = dir/200000.0 + 0.0015;
	//printf("\t\tservo_pw: %.5f\n", servo_pw);
	
	if (servo_pw < min_pw) {
		servo_pw = min_pw;
	}
	if (servo_pw > max_pw) {
		servo_pw = max_pw;
	}
	
	PWM_pulse_set(servo_pw);
	
}