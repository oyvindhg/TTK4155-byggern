/*
 * timer_driver.c
 *
 * Created: 30.10.2016 15:16:09
 *  Author: WD
 */ 

#ifndef PRESCALER
#define PRESCALER 1024	//This is just a macro, it has no data type.
#endif

ISR(TIMER0_OVF_vect){
	printf("\t\toverflow\n");
}


void timer_init(){
	//-------------INITIALIZE TIMER INPUT-----------------
	
	int prescaler = 1024;
	// TOP = 313
	
	/*
	// Disable global interrupts
	cli();

	// enable timer overflow interrupt for Timer0
	TIMSK=(1<<TOIE0);

	// start timer0 with /256 prescaler
	if (prescaler == 256){
		TCCR0 = (1<<CS02);
	}
	else if (prescaler == 1024){
		TCCR0 = (1<<CS02) | (1<<CS00);
	}

	// Enable global interrupts
	sei();
	*/
}