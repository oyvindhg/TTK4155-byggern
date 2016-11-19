/*
 * PID.h
 *
 * Created: 17.11.2016 10:01:36
 *  Author: WD
 */ 


#ifndef PID_H_
#define PID_H_

typedef enum{
	EASY,
	MEDIUM,
	HARD
} difficulty_t;

void PID_update_pos_ref(int16_t pos);
void PID_init();
void PID_update(difficulty_t);

#endif /* PID_H_ */