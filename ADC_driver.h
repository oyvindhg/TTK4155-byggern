/*
 * ADC.h
 *
 * Created: 15.09.2016 15:46:43
 *  Author: Whiskey Dicks
 */ 


#ifndef ADC_H_
#define ADC_H_

void ADC_init(void);

typedef enum {CHANNEL1, CHANNEL2, CHANNEL3, CHANNEL4} channel_t; //Begynner enum på 0 eller 1? Må vi definere selv?

char ADC_get_data(void);

void ADC_start_read(channel_t channel);

#endif /* ADC_H_ */