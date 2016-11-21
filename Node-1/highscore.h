/*
 * highscore.h
 *
 * Created: 19.11.2016 17:20:09
 *  Author: WD
 */ 


#ifndef HIGHSCORE_H_
#define HIGHSCORE_H_

typedef struct {
	char name[3];
	uint8_t score;
} highscore;

void read_score(highscore* hs, int8_t mem_loc);
void write_score(highscore hs, int8_t mem_loc);
void highscore_init();
void print_highscore();
uint8_t check_score(uint8_t);
void insert_score(char* name, uint8_t score);
uint8_t check_score(uint8_t score);
void create_nickname();



#endif /* HIGHSCORE_H_ */