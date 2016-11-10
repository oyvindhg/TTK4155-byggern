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
	
	// Set direction pin to output
	set_bit(DDRH, PH1);
	
	//--------------------Set encoder pins to output and input mode----------------------
	
	//Output Enable pin (active low): !OE
	set_bit(DDRH, PH5);
	
	//Selection pin: SEL
	set_bit(DDRH, PH3);
	
	//Reset pin: RST
	set_bit(DDRH, PH6);
	set_bit(PORTH, PH6);
	
	//Set data bits to input:
	clear_bit(DDRK, PK0);
	clear_bit(DDRK, PK1);
	clear_bit(DDRK, PK2);
	clear_bit(DDRK, PK3);
	clear_bit(DDRK, PK4);
	clear_bit(DDRK, PK5);
	clear_bit(DDRK, PK6);
	clear_bit(DDRK, PK7);
	
	
	
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
	
	/*-------------------------------------------------*
	 |	    clear/set SEL opposite of datasheet        |
	 |  We don't know why, perhaps faulty motor box?   |
	 *-------------------------------------------------*/
	
	
	//Set !OE low to enable output of encoder
	clear_bit(PORTH, PH5);
	
	//Set SEL low to get low byte
	clear_bit(PORTH, PH3);
	
	//Wait about 20 microseconds
	_delay_us(60);
	
	//Read LSB
	uint8_t low = PINK;
	
	//Set SEL high to get HIGH byte
	set_bit(PORTH, PH3);
	
	//Wait about 20 microseconds
	_delay_us(60);
	
	//Read MSB
	uint8_t high = PINK;
	
 	//Toggle !RST to reset encoder
 	clear_bit(PORTH, PH6);
 	_delay_us(200);
 	set_bit(PORTH, PH6);
	
	//Set !OE high to disable output of encoder
	set_bit(PORTH, PH5);
	
	int16_t rot = (int16_t) ( (high << 8) | low);
	
	return rot;
}