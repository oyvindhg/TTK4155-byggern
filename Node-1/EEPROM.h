/*
 * EEPROM.h
 *
 * Created: 20.11.2016 10:25:42
 *  Author: WD
 */ 


#ifndef EEPROM_H_
#define EEPROM_H_

#include <avr/io.h>

void EEPROM_write(uint8_t address, uint8_t data);

uint8_t EEPROM_read(uint8_t address);

void EEPROM_reset(uint8_t num);

#endif /* EEPROM_H_ */