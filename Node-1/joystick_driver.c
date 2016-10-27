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

typedef struct {
	int x;
	int y;
} volatile joystick_position_T2;

#include "joystick_driver.h"
#include "ADC_driver.h"
#include "bit_macros.h"


volatile joystick_position_T2 position;		//husk å enable joystick_get_position()
volatile int x_pos;
volatile int y_pos;
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
	//printf("\t\toverflow\n");
	channel_t channel;
	char data_char = get_ADC_data();
	int32_t data = (int32_t)data_char;
	
	//printf("Data read: %d\n",extraVar);
	switch(contr_state){
		case(JOYSTICK_X):
//			position.x = ((data-x_offset)*200 )/ (joy_x_V_max - joy_x_V_min);
			x_pos = ((data-x_offset)*200 )/ (joy_x_V_max - joy_x_V_min);			
			contr_state = JOYSTICK_Y;
			channel = CHANNEL2;
			//printf("\nX1: %d\n", position.x);
			break;
		case(JOYSTICK_Y):
//			position.y = ((data-y_offset)*200 )/ (joy_y_V_max - joy_y_V_min);
			y_pos = ((data-y_offset)*200 )/ (joy_y_V_max - joy_y_V_min);
			contr_state = LEFT_SLIDER;
			channel = CHANNEL3;
//			printf("\nX1: %d", position.x);
//			printf("\tY1: %d\n", position.y);
// 			printf("\nX1: %d", x_pos);
// 			printf("\tY1: %d\n", y_pos);
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
	
	// Button inputs:
	clear_bit(DDRB, PB0);	//Joystick button
	set_bit(PORTB, PB0);		//Set pull-up resistor
	clear_bit(DDRB, PB1);	//Right button
	clear_bit(DDRB, PB2);	//Left button
	
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
			//printf("joy: %d\n", !test_bit(PORTB, PB0));
			return !test_bit(PINB, PINB0);
		case LBUTTON :
			return test_bit(PINB, PINB2);
		case RBUTTON :
			//printf("R: %d\n", test_bit(DDRB, PB2));
			return test_bit(PINB, PINB1);
		default:
			printf("Not valid button");
			return EXIT_FAILURE;
		}

}


// joystick_position_t joystick_get_position() {
// 	return position;
// }


joystick_direction_t joystick_get_direction() {
	//printf("\tPOS.Y1: %d\n",position.y);
	
//	int x = position.x;
//	int y = position.y;
	int x = x_pos;
	int y = y_pos;
//  	printf("\t\t\tx: %d",x);
//  	printf("\ty: %d\n", y);
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
		if (abs(y) < 65){
/*			printf("\t\t\tPOS.Y2: %d\n",position.y);*/
			return NEUTRAL;
		}
		else if (y < 0){
/*			printf("\t\t\tPOS.Y2: %d\n",position.y);*/
			return DOWN;
		}
		else {
/*			printf("\t\t\tPOS.Y2: %d\n",position.y);*/
			return UP;
		}
	}
}

int slider_get_left(void){
	return sliders.left;
}
int slider_get_right(void){
	return sliders.right;
}