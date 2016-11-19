/*
 * PID.c
 *
 * Created: 17.11.2016 10:01:21
 *  Author: WD
 */ 

#ifndef F_CPU
#define F_CPU 16000000UL
#endif


#include <avr/io.h>
#include <avr/interrupt.h>

#include "PID.h"
#include "motor_driver.h"

int16_t rot_max = -8800;
int16_t rot_min = 100;

int16_t ref_position = 0;
double motor_middle = 0;
double Kp = 2;
double Ki = 4;
double Kd = 0.1;
double integral = 0;
int16_t prev_error = 0;
double dt = 0.016;

ISR(TIMER2_OVF_vect){
	
	//printf("%f\n", integral);
	
	
	int16_t motor_rot = motor_read_rotation(0);
	double measured = (motor_rot + motor_middle) / (-motor_middle/100);
	
	int16_t ref = ref_position;
	
	int16_t error = ref - measured;
	integral = integral + error * dt;
	
	if (error < 1){
		integral = 0;
	}
	
	double derivative = -(error - prev_error)/dt;
	
	int16_t power_signed = 0;
	uint8_t power = 0;
	power_signed = Kp * error + Ki  * integral + Kd * derivative;
	
	prev_error = error;
	
	if (power_signed < 0){
		motor_set_direction(LEFT);
		if (power_signed > -150){
			power = -power_signed;
		}
		else {
			power = 150;
		}
	}
	else{
		motor_set_direction(RIGHT);
		if (power_signed < 150){
			power = power_signed;
		}
		else {
			power = 150;
		}
	}
	motor_set_speed(power);
}

void PID_init(){
	
	 motor_middle = -(rot_max + rot_min) / 2;
	
	//-------------INITIALIZE TIMER INPUT-----------------
	
	// Disable global interrupts
	cli();
	
	// enable timer overflow interrupt for Timer2
	TIMSK2=(1<<TOIE2);
	
	// start timer2 with /1024 prescaler
	
	TCCR2B = (1<<CS20) | (1<<CS21) | (1<<CS22);
	
	// Enable global interrupts
	sei();
	
	//---------------------------------------------------
	
}

void PID_update_pos_ref(int16_t pos){
	ref_position = pos;
}

void PID_update(difficulty_t difficulty){
	
	switch (difficulty){
		case EASY:
			Kp = 2.5;
			Ki = 2;
			Kd = 0.1;
			break;
		case MEDIUM:
			Kp = 2;
			Ki = 4;
			Kd = 0.1;
			break;
		case HARD:
			Kp = 2;
			Ki = 4;
			Kd = 0.1;
			break;
		}
	
	//printf("Difficulty updated!\nKp:%f\nKi:%f\nKd:%f\n", Kp, Ki, Kd);
	
}