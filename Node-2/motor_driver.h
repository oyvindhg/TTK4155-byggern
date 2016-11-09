/*
 * motor_driver.h
 *
 * Created: 09.11.2016 13:56:20
 *  Author: oyvindhg
 */ 


#ifndef MOTOR_DRIVER_H_
#define MOTOR_DRIVER_H_

typedef enum {LEFT, RIGHT} motor_direction_t;


void motor_init();
void motor_set_direction(motor_direction_t);
void motor_set_speed(uint8_t speed);
int16_t motor_read_rotation();


#endif /* MOTOR_DRIVER_H_ */