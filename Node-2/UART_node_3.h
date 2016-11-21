/*
 * UART_node_3.h
 *
 * Created: 20.11.2016 23.01.53
 *  Author: Per Arne
 */ 

#ifndef UART_DRIVER_H_
#define UART_DRIVER_H_

void UART_init_3(unsigned long clock_speed);
int put_char_3(unsigned char c);
int get_char_3(void);

#endif /* MAX233_DRIVER_H_ */



#endif /* UART_NODE_3_H_ */