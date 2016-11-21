/*
 * byggern_gr60_node3.c
 *
 * Created: 19.11.2016 13.35.32
 * Author : Whiskey dick
 */ 
#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "Music.h"
#include "bit_macros.h"
#include "UART_driver.h"

void music_delay(uint16_t delay) {
	while (delay--) {
		_delay_us(0.75);
	}
}

int main(void) {
	unsigned long clock = F_CPU;
	UART_init(clock);
//	receive = get_char();
// 	set_bit(DDRD,PD5);
// 	set_bit(PORTD,PD5);
	set_bit(DDRD, melody_pin);
	uint8_t bpm = 0;
	uint8_t note_pointer = 0;
	uint16_t note;
	uint32_t length;
	uint16_t key;
	uint32_t num_cycles;	
	uint16_t* current_song;
	char receive = 0;
	key = 0;
	note = 0;
	receive = 2;
//unsigned char receive2;
	
	while(1) {
		// Song finished - what to do next? 
 		if (note == 0 && key == 0) {
			 receive = get_char();
			 if (receive == ZELDA) {
				 current_song = zelda_secret;
				 bpm = zelda_secret[0];
			} else if (receive == MARIO) {
				 current_song = mario_melody;
				 bpm = mario_melody[0];
			} else if (receive == UNDERWORLD){
				 current_song = underworld_melody;
				 bpm = underworld_melody[0];
			 }
			note_pointer = 0;
		}
		
// 		receive2 = get_char_imm();
// 		if (receive2 !=0) {
// 			receive = get_char();
// 			current_song = zelda_secret;
// 			note_pointer = 0;	
// 			bpm = zelda_secret[0];	
// 		}	
		
		// Play next tone in the song
		note_pointer++;
		note = current_song[note_pointer];
		note_pointer++;
		key = current_song[note_pointer];
		length = note/bpm;
		
		// Make room for pause notes
		if (key == 0) {
			key = 500;
			num_cycles = length*1000/2/key;
		} 
		else {
			num_cycles = length*1000/2/key;				// Duration of key-tone
		}
		
		// Play tone on Melody_pin
		for (uint32_t i = 0; i < num_cycles; i++) {
			if (key == 500) {
				clear_bit(PORTD,melody_pin);
				music_delay(key);
				clear_bit(PORTD,melody_pin);
				music_delay(key);
			} else {
				set_bit(PORTD,melody_pin);
				music_delay(key);
				clear_bit(PORTD, melody_pin);
				music_delay(key);
			}
		}
		
		// Small delay between each tone
		_delay_us(SIXTEENTH);
		// If key was zero, set zero again in case song is over
		if (key == 500) {
			key = 0;
		}
	}
	
}