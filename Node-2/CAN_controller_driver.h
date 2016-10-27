/*
 * CAN_controller_driver.h
 *
 * Created: 13.10.2016 09:08:20
 *  Author: Whiskey Dicks
 */


#ifndef CAN_CONTROLLER_DRIVER_H_
#define CAN_CONTROLLER_DRIVER_H_

#include <stdint.h>
#include "SPI_driver.h"

uint8_t mcp_2515_init(void);

void mcp_2515_set_mode(uint8_t mode);
void mcp_2515_reset(void);

uint8_t mcp_2515_read(uint8_t address);
void mcp_2515_write(uint8_t address, uint8_t data);

void mcp_2515_request_to_send(char buffer);
void mcp_2515_bit_modify(uint8_t adress, uint8_t mask, uint8_t data);
uint8_t mcp_2515_read_status(void);

// Page 63 in the datasheet

#endif /* CAN_CONTROLLER_DRIVER_H_ */