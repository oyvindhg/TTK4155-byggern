/*
 * CAN.h
 *
 * Created: 13.10.2016 17:26:53
 *  Author: Whiskey Dicks
 */


#ifndef CAN_H_
#define CAN_H_

#include "CAN_controller_driver.h"

typedef struct {
	unsigned int id;
	uint8_t length;
	uint8_t data[8];
} can_message;


void can_init(void);
void can_message_send(can_message* message);
void can_error(void);
void can_transmit_complete(void);
can_message* can_data_receive(void);
void can_int_vect(void);

#endif /* CAN_H_ */