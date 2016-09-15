/*
 * ADC.c
 *
 * Created: 15.09.2016 15:46:33
 *  Author: Whiskey Dicks
 */
#include <stdlib.h>
#include <stdint.h>
#include "ADC_driver.h"

#ifndef ADC_FIRST_ADDRESS
#define ADC_FIRST_ADDRESS 0x1400	//This is just a macro, it has no data type.
#endif

int ADC_write(uint16_t address, char data){
	
	if (address > 0x3FF){
		printf("ADC error, trying to write to an address that is too big\n");
		return EXIT_FAILURE;
	}
	
	volatile char* ext_ram = ADC_FIRST_ADDRESS;	//Create a pointer to the array of all addresses we will write to. ADC starting at 0x1400. ext_ram[0x3FF] is maximum because 0x1400 + 0x3FF = 0x17FF!
	ext_ram[address] = data;
	
	return 0;
}