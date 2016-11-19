/*
 * IR_driver.h
 *
 * Created: 03.11.2016 17:58:39
 *  Author: Whiskey Dick
 */ 


#ifndef IR_DRIVER_H_
#define IR_DRIVER_H_


void IR_init(void);

uint16_t IR_average_filter(void);
uint16_t IR_game_over(void);

#endif /* IR_DRIVER_H_ */