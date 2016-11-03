/*
 * servo_driver.h
 *
 * Created: 03.11.2016 11:20:51
 *  Author: Whiskey Dicks
 */ 


#ifndef SERVO_DRIVER_H_
#define SERVO_DRIVER_H_

void servo_init(unsigned long clock_speed);

void set_servo(int servo_dir);

#endif /* SERVO_DRIVER_H_ */