/*
 * CAN.h
 *
 * Created: 13.10.2016 17:26:53
 *  Author: Whiskey Dicks
 */


#ifndef CAN_H_
#define CAN_H_

#include "CAN_controller_driver.h"

typedef enum{
	GAME,
	DIFFICULTY,
	SONG
} message_type_t;

typedef struct {
	unsigned int id;
	uint8_t length;
	uint8_t data[8];
} can_message;


void can_init(uint8_t mode);
void can_message_send(can_message* message);

can_message can_handle_messages();
int can_error(void);
int can_transmit_complete(int);
void can_message_receive(int, can_message* message);
void can_int_vect(uint8_t*);
uint8_t can_interrupt(void);

#endif /* CAN_H_ */