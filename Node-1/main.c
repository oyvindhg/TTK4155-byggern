/*
 * main.c
 *
 * Created: 03.09.2016 12:26:04
 *  Author: Whiskey dicks

 Crystal oscillator frequency: 4.9152 MHz

 Tip for debug of a variable: Use volatile when initializing the variable, then press Start Debugging and Break. Then add the variable to the watch-list after right clicking it. Now it can be viewed in debug mode.

*/

#ifndef F_CPU
#define F_CPU 4915200UL	//This is just a macro, it has no data type.
#endif

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#include "bit_macros.h"
#include "UART_driver.h"
#include "XMEM.h"
#include "SRAM_driver.h"
#include "ADC_driver.h"
#include "joystick_driver.h"
#include "OLED_driver.h"
#include "OLED_menu.h"
#include "CAN.h"
#include "game.h"
#include "highscore.h"

/*
void exercise1(void) {

	//UART

	put_char(get_char() + 1);		//Returns the character next in the alphabet.

	printf("\nhello world!\n");

}

void exercise2(void) {

	//SRAM

	char data = 'c';

	volatile char* ext_ram = 0x1000;

	SRAM_test();

	while(1) {
		ext_ram[0x000] = data;
		//printf("OLED command\n");
		_delay_ms(3000);
		ext_ram[0x300] = data;
		//printf("OLED data\n");
		_delay_ms(3000);
		ext_ram[0x400] = data;
		//printf("ADC\n");
		_delay_ms(3000);
		ext_ram[0x800] = data;
		//printf("SRAM\n");
		_delay_ms(3000);
	}

}

void exercise3(void) {

	//Joystick

	joystick_position_t position;
	joystick_direction_t direction;

	while(1){

		position = joystick_get_position();

		printf("Joystick: \tx: %d \t\tSlider:\tleft: %d \n", position.x, slider_get_left());
		printf("\t\ty: %d \t\t\tright: %d \n\n", position.y, slider_get_right());


		if (joystick_button(JOYSTICKBUTTON)){
			printf("JOYSTICK BUTTON\n");
		}

		if (joystick_button(LBUTTON)){
			printf("LEFT BUTTON\n");
		}

		if (joystick_button(RBUTTON)){
			printf("RIGHT BUTTON\n");
		}


		direction = joystick_get_direction();

		printf("\nDirection: %d\n\n", direction);

		//printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n\n");

		//_delay_ms(1000);
	};
}

void exercise4(void) {

	//OLED

	while(1){
		oled_menu_selection();
		_delay_ms(200);
	}

}

void exercise5(void) {

	can_init(MODE_LOOPBACK);

	can_message test;
	test.id		= 1337;
	test.data[0]	= 'H';
	test.data[1]	= 'e';
	test.data[2]	= 'l';
	test.data[3]	= 'l';
	test.data[4]	= 'o';
	test.length	= 5;

	can_message test2;
	test2.id		= 1338;
	test2.data[0]	= 'W';
	test2.data[1]	= 'o';
	test2.data[2]	= 'r';
	test2.data[3]	= 'l';
	test2.data[4]	= 'd';
	test2.length	= 5;


	can_message_send(&test);
	can_message_send(&test2);

	while(1){

		if ( can_interrupt()){
			can_handle_messages();
		}

		_delay_ms(30);
	}

}

void exercise6(){
	can_message joy_pos;
	joystick_position_t position;

	uint8_t id = 0;

	while(1){
		position = joystick_get_position();
		joy_pos.data[0] = position.x;
		joy_pos.data[1] = position.y;
		joy_pos.length = 2;
		joy_pos.id = id;

		//printf("x: %d, y: %d\n", joy_pos.data[0], joy_pos.data[1]);

		can_message_send(&joy_pos);

		id = id + 1;
		_delay_ms(30);
	}
}
*/

int main(void) {

	int prescaler_joystick_timer = 1024;

	unsigned long clock_speed = F_CPU;

	UART_init(clock_speed);
	XMEM_init();

	ADC_init();

	joystick_init(prescaler_joystick_timer);

	oled_init();

	oled_menu_init();
	can_init(MODE_NORMAL);

	//--------------
	//EEPROM_reset(12);
	//--------------

	highscore_init();


	uint8_t play_again = 1;
	uint8_t score;
	menu_option_t menu_choice;
	char name[4] = "   \0";
	can_message song;
	while(1){
		menu_choice = oled_menu_selection();
		play_again = 1;
		switch(menu_choice){
			case PLAY_GAME:

				while (play_again){
					oled_print_status(PLAY_GAME);
					score = game_play();
					oled_print_status(GAME_OVER);
					while (1){
						_delay_ms(400);
						if (joystick_button(LBUTTON)){
							play_again = 0;
							break;
						}
						else if (joystick_button(RBUTTON)){
							play_again = 1;
							break;
						}
					}
				}

				if (check_score(score)){
					oled_print_status(SAVE_HIGHSCORE);
					while (1){
						_delay_ms(200);
						if (joystick_button(LBUTTON)){
							break;
						}
						else if (joystick_button(RBUTTON)){
							_delay_ms(200);
							create_nickname(name);
							insert_score(name, score);
							break;
						}
					}
				}

				print_highscore();
				_delay_ms(2000);
				goto_menu(LBUTTON);
				break;

			case HIGHSCORE:
				print_highscore();
				break;

			case AUTO_CALIBRATE:
				joystick_auto_calibrate();
				oled_print_status(AUTO_CALIBRATE);
				_delay_ms(1000);
				break;

			case EASY:
				send_difficulty(0);
				oled_print_status(EASY);
				_delay_ms(1000);
				goto_menu(LBUTTON);
				goto_menu(LBUTTON);
				break;

			case MEDIUM:
				send_difficulty(1);
				oled_print_status(MEDIUM);
				_delay_ms(1000);
				goto_menu(LBUTTON);
				goto_menu(LBUTTON);
				break;

			case HARD:
				send_difficulty(2);
				oled_print_status(HARD);
				_delay_ms(1000);
				goto_menu(LBUTTON);
				goto_menu(LBUTTON);
				break;

			case ZELDA:
				song.id = 2;
				song.length = 1;
				song.data[0] = 0;
				can_message_send(&song);
				break;

			case MARIO:
				song.id = 2;
				song.length = 1;
				song.data[0] = 1;
				can_message_send(&song);
				break;

			case UW:
				song.id = 2;
				song.length = 1;
				song.data[0] = 2;
				can_message_send(&song);
				break;

			case NONE:
				break;
		}
		_delay_ms(200);
	}

	return 0;
}
