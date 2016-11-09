/*
 * motor_driver.c
 *
 * Created: 09.11.2016 13:56:03
 *  Author: oyvindhg
 */ 

#include <avr/io.h>
#include <util/delay.h>

#include "bit_macros.h"
#include "motor_driver.h"

void motor_init(){
	
	// Enable motor
	set_bit(DDRH, PH4);
	set_bit(PORTH, PH4);
	
	// Set direction pin to output and the direction to (right?)
	set_bit(DDRH, PH1);
	set_bit(PORTH, PH1);
	
	//--------------------Set encoder pins to output and input mode----------------------
	
	//Output Enable pin (active low): !OE
	set_bit(DDRH, PH5);
	
	//Selection pin: SEL
	set_bit(DDRH, PH3);
	
	//Reset pin: RST
	set_bit(DDRH, PH6);
	
	//Set data bits to input:
	clear_bit(DDRF, PC0);
	clear_bit(DDRF, PC1);
	clear_bit(DDRF, PC2);
	clear_bit(DDRF, PC3);
	clear_bit(DDRF, PC4);
	clear_bit(DDRF, PC5);
	clear_bit(DDRF, PC6);
	clear_bit(DDRF, PC7);
	
	
	
}

void motor_set_direction(motor_direction_t direction){
	switch (direction){
		case(LEFT):
			clear_bit(PORTH, PH1);
			break;
		case(RIGHT):
			set_bit(PORTH, PH1);
			break;
	}
}

void motor_set_speed(uint8_t speed){
	DAC_send(speed);
}

int16_t motor_read_rotation(){
	
	//Set !OE low to enable output of encoder
	clear_bit(PORTH, PH5);
	
	//Set SEL low to get high byte
	clear_bit(PORTH, PH3);
	
	//Wait about 20 microseconds
	_delay_ms(0.025);
	
	//Read MSB
	int16_t high = PINF;
	
	//Set SEL high to get low byte
	set_bit(PORTH, PH3);
	
	//Wait about 20 microseconds
	_delay_ms(0.025);
	
	//Read LSB
	int8_t low = PINF;
	
	//Toggle !RST to reset encoder
	toggle_bit(PINH, PH6);
	
	//Set !OE high to disable output of encoder
	set_bit(PORTH, PH5);
	
	int16_t rot = high * 0b10000000 + low;
	return rot;
}