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

//Recomended functions from the assignment text
void oled_reset(void);
void oled_home(void);
void oled_goto_line(line);
void oled_goto_column(column);
void oled_clear_line(lie);
void oled_pos(row, column);


#endif /* OLED_DRIVER_H_ */