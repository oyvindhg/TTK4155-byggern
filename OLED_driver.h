/*
 * OLED_driver.h
 *
 * Created: 29.09.2016 14:30:47
 *  Author: Whiskey Dicks
 */ 


#ifndef OLED_DRIVER_H_
#define OLED_DRIVER_H_

void write_data(uint8_t data);
void oled_init(void);
void oled_printf(char* data, ...);
int oled_put_char(unsigned char);

typedef enum{HORIZONTAL_MODE, VERTICAL_MODE, PAGE_MODE} adressing_mode;

void oled_set_adressing_mode(adressing_mode mode);

//Recomended functions from the assignment text
void oled_reset(void);
void oled_home(void);
void oled_goto_line(int line);
void oled_goto_column(int column);
void oled_clear_line(int line);
void oled_pos(int row, int column);
void write_command(uint8_t command);

#endif /* OLED_DRIVER_H_ */