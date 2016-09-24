/*
 * joystick_driver.c
 *
 * Created: 22.09.2016 10:51:33
 *  Author: Whiskey Dicks
 */ 

#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdint.h>

#include "joystick_driver.h"
#include "ADC_driver.h"
#include "bit_macros.h"


volatile joystick_position_t position;
volatile sliders_position_t sliders;
volatile state contr_state;

volatile int joy_x_V_min = 0;
volatile int joy_x_V_max = 255;
volatile int joy_y_V_min = 0;
volatile int joy_y_V_max = 255;

volatile int x_offset;
volatile int y_offset;

volatile int slide_left_V_min = 0;
volatile int slide_left_V_max = 255;
volatile int slide_right_V_min = 0;
volatile int slide_right_V_max = 255;


// timer0 overflow
ISR(TIMER0_OVF_vect){

	channel_t channel;
	int32_t data = (int32_t)get_ADC_data();
	switch(contr_state){
		case(JOYSTICK_X):
			position.x = ((data-x_offset)*200 )/ (joy_x_V_max - joy_x_V_min);
			contr_state = JOYSTICK_Y;
			channel = CHANNEL2;
			break;
		case(JOYSTICK_Y):
			position.y = ((data-y_offset)*200 )/ (joy_y_V_max - joy_y_V_min);
			contr_state = LEFT_SLIDER;
			channel = CHANNEL3;
			break;
		case(LEFT_SLIDER):
			sliders.left = (data * 200)/ (slide_left_V_max - slide_left_V_min)  - 100;
			contr_state = RIGHT_SLIDER;
			channel = CHANNEL4;
			break;
		case(RIGHT_SLIDER):
			sliders.right = (data * 200) / (slide_right_V_max - slide_right_V_min) - 100;
			contr_state = JOYSTICK_X;
			channel = CHANNEL1;
			break;
}
	ADC_start_read(channel);
}

void joystick_auto_calibrate(){
	
	ADC_start_read(CHANNEL1);
	_delay_ms(1);
	x_offset = (int)get_ADC_data();
	
	ADC_start_read(CHANNEL2);
	_delay_ms(1);
	y_offset = (int)get_ADC_data();
	
}

void joystick_init(int prescaler){
	
	// Button inputs
	clear_bit(DDRB, PB0);
	clear_bit(DDRB, PB1);
	clear_bit(DDRB, PB2);
	
	joystick_auto_calibrate();
		
	contr_state = JOYSTICK_X;
	ADC_start_read(CHANNEL1);
	
	//-------------INITIALIZE TIMER INPUT-----------------
	
	// Disable global interrupts
	cli();
	
	// enable timer overflow interrupt for Timer0
	TIMSK=(1<<TOIE0);
	
	// start timer0 with /256 prescaler
	if (prescaler == 256){
		TCCR0 = (1<<CS02);
	}
	else if (prescaler == 1024){
		TCCR0 = (1<<CS02) | (1<<CS00);
	}
	
	// Enable global interrupts
	sei();
	
	//---------------------------------------------------


}


void joystick_manual_calibrate(){
	return;
}

int joystick_button(usb_button_t button){
	
	switch (button) {
		case JOYSTICKBUTTON :
			return test_bit(DDRB, PB0);
		case LBUTTON :
			return test_bit(DDRB, PB1);
		case RBUTTON :
			return test_bit(DDRB, PB2);
		default:
			printf("Not valid button");
			return EXIT_FAILURE;
		}

}


joystick_position_t joystick_getPosition() {
	return position;
}


joystick_direction_t joystick_getDirection() {
	int x = position.x;
	int y = position.y;
	if (abs(x) >= abs(y)){
		if (abs(x) < 10){
			return NEUTRAL;
		}
		else if (x < 0){
			return LEFT;
		}
		else {
			return RIGHT;
		}
	} 
	else{
		if (abs(y) < 10){
			return NEUTRAL;
		}
		else if (y < 0){
			return DOWN;
		}
		else {
			return UP;
		}
	}
}

