/*
 * timer_driver.h
 *
 * Created: 30.10.2016 15:16:29
 *  Author: WD
 */ 


#ifndef PWM_DRIVER_H_
#define PWM_DRIVER_H_

void PWM_init(float period_microsec, unsigned long clock_frequency);

void PWM_set_period(float sec);

void PWM_pulse_set(float sec);


#endif /* PWM_DRIVER_H_ */