/*
 * PWM_driver.c
 *
 * Created: 30.10.2016 15:16:09
 *  Author: WD
 */ 

#include <avr/io.h>

#include "PWM_driver.h"
#include "bit_macros.h"


static uint16_t pwm_timer_freq;

uint16_t pulse;


void PWM_init(float period_sec, unsigned long clock_frequency){
	
	uint16_t prescaler = 256;
	
	//Fast PWM-MODE (mode 14, table 17-2)
	set_bit(TCCR1B, WGM13);
	set_bit(TCCR1B, WGM12);
	set_bit(TCCR1A, WGM11);
	clear_bit(TCCR1A, WGM10);
	
	//Set compare output on PB5 (OC1A)
	set_bit(TCCR1A, COM1A1);
	clear_bit(TCCR1A, COM1A0);
	pwm_timer_freq = (uint32_t)clock_frequency/prescaler;
	PWM_set_period(period_sec);
	

	// Set PB5 to output mode
	set_bit(DDRB, PB5);
}

void PWM_set_period(float sec){
	
	// Set prescaler 256
	set_bit(TCCR1B, CS12);
	clear_bit(TCCR1B, CS11);
	clear_bit(TCCR1B, CS10);
	
	// Set period to 20 ms (prescaler 256)
	uint16_t period = pwm_timer_freq*sec - 0.5;
	ICR1 = period;
	
}

void PWM_pulse_set(float sec) {
	
	pulse = pwm_timer_freq*sec - 0.5;
	OCR1A = pulse;
}