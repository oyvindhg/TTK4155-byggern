/*
 * XMEM.c
 *
 * Created: 15.09.2016 14:12:21
 *  Author: Whiskey Dicks
 */ 

#include <avr/io.h>
#include "bit_macros.h"

void XMEM_init(void){

	set_bit(MCUCR,SRE);		//Enable External Memory Interface. PE1 is automatically controlled as this command takes control.
	set_bit(SFIOR,XMM2);	//Remove 4 Most Significant Bits from address so that JTAG interface doesn't crash

}