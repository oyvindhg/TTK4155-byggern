/*
 * IR_driver.c
 *
 * Created: 03.11.2016 17:58:26
 *  Author: Whiskey Dick
 */ 


clear_bit(DDRF,PF0);
int sensor_value = 0;
uint8_t num_readings = 4;
uint8_t readings[num_readings];
uint8_t read_index = 0;
uint8_t total = 0;

void IR_init() {
	for (uint8_t this_reading = 0; this_reading < num_readings; this_reading++) {
		readings[this_reading] = 0;
	}
	
	sensor_value = analog_read(PF0);
	digital
}

uint8_t IR_average_filter() {
	total = total - readings[read_index];
	
	readings[read_index] = analog_read(PF0);
	
	total = total + readings[read_index];
	
	read_index = read_index + 1;
	
	if (read_index >= num_readings) {
		read_index = 0;
	}
	
	uint8_t average = total / num_readings;
	
	return average;
}