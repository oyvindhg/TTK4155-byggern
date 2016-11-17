/*
 * IR_driver.c
 *
 * Created: 03.11.2016 17:58:26
 *  Author: Whiskey Dick
 */ 

#include <AVR/io.h>

#include "IR_driver.h"
#include "ADC_driver.h"

uint8_t num_readings = 4;
uint16_t readings[4];
uint8_t read_index = 0;
uint16_t total = 0;

void IR_init() {
	ADC_init();
	
	for (uint8_t this_reading = 0; this_reading < num_readings; this_reading++) {
		readings[this_reading] = 0;
	}
	
	readings[read_index] = ADC_read();
	total = readings[read_index];
}

uint16_t IR_average_filter() {
	total = total - readings[read_index];
	
	readings[read_index] = ADC_read();
	
	printf("ADC: %d", readings[read_index]);
	
	total = total + readings[read_index];
	
	read_index = read_index + 1;
	
	if (read_index >= num_readings) {
		read_index = 0;
	}
	
	uint16_t average = total / num_readings;
	printf("\t\tAVG: %d\n", average);
	return average;
}

uint16_t IR_goal_counter(uint8_t init_flag) {
	static goal_counter;
	if (!init_flag) {
		goal_counter = 0;
	}
	if (IR_average_filter() < 125) {
		goal_counter = goal_counter + 1;
		//printf("\t*-----GAME OVER----*\n");
		return goal_counter;
	}
	else {
		return goal_counter;
	}
}