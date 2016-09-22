/*
 * joystick_driver.c
 *
 * Created: 22.09.2016 10:51:33
 *  Author: Whiskey Dicks
 */ 

#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include "joystick_driver.h"
#include "ADC_driver.h"
#include "bit_macros.h"
#include <util/delay.h>


volatile joystick_position_t position;
volatile sliders_position_t sliders;

volatile state contr_state= JOY_X;

volatile float joy_x_V_min = 0;
volatile float joy_x_V_max = 255;
volatile float joy_y_V_min = 0;
volatile float joy_y_V_max = 255;

volatile float x_offset = 0;
volatile float y_offset = 0;


volatile float slide_left_V_min = 0;
volatile float slide_left_V_max = 255;
volatile float slide_right_V_min = 0;
volatile float slide_right_V_max = 255;

// timer0 overflow
ISR(TIMER0_OVF_vect){
	
	
	channel_t channel;
	
	float data = (float)get_ADC_data();
	
	switch(contr_state){
		case(JOY_X):
			position.x = (int) ( (data-x_offset) / (joy_x_V_max - joy_x_V_min) * 200);
			contr_state = JOY_Y;
			channel = CHANNEL2;
			if (position.x>=13270)
				printf("S");
			else if (position.x <= 40 && position.x >=-40)
				printf("N");
 			else
 				printf("M");
			break;
		case(JOY_Y):
			position.y = (int) ( (data-y_offset) / (joy_y_V_max - joy_y_V_min) * 200);
			contr_state = LEFT_SLIDER;
			channel = CHANNEL3;
// 			if (position.y>=40)
// 				printf("s");
// 			else if (position.y <= 40 && position.y >=-40)
// 				printf("n");
// 			else
// 				printf("m");
			break;
		case(LEFT_SLIDER):
			sliders.left = (int) (data / (slide_left_V_max - slide_left_V_min)  * 200 - 100);
			contr_state = RIGHT_SLIDER;
			channel = CHANNEL4;
			break;
		case(RIGHT_SLIDER):
			sliders.right = (int) (data / (slide_right_V_max - slide_right_V_min) * 200 - 100);
			contr_state = JOY_X;
			channel = CHANNEL1;
			break;
	}
			
	ADC_start_read(channel);
}

void joystick_auto_calibrate(){
	
	ADC_start_read(CHANNEL1);
	_delay_ms(1);
	x_offset = (float)get_ADC_data();
	
	ADC_start_read(CHANNEL2);
	_delay_ms(1);
	y_offset = (float)get_ADC_data();
	
}

void joystick_init(int prescaler){
	
	// Button inputs
	clear_bit(DDRB, PB0);
	clear_bit(DDRB, PB1);
	clear_bit(DDRB, PB2);
	
	
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
	
	joystick_auto_calibrate();
	
	contr_state = JOY_X;
	ADC_start_read(CHANNEL1);

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
	return LEFT;
}

