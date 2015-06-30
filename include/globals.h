/*
 * globals.h
 *
 * Created: 07.06.2015 10:18:59
 *  Author: TwoBit
 */ 


#ifndef GLOBALS_H_
#define GLOBALS_H_

#ifndef F_CPU
#define F_CPU 10000000UL
#endif

#include <util/delay.h>
#include <avr/io.h>

extern volatile uint8_t key;
extern volatile uint8_t print_graph;
extern volatile uint8_t print_temp_flag;

// Measurment Values:
extern volatile int8_t temp;
extern volatile uint16_t ldr_value;

// Configure Parameters:
extern volatile int sample_rate;
extern volatile int range_min;
extern volatile int range_max;
extern volatile int temp_min;
extern volatile int temp_max;

enum KEYPAD_BUTTONS{
	S1 = 1,
	S2 = 2,
	S3 = 3,
	S4 = 4,
	S5 = 5,
	S6 = 6,
	S7 = 7,
	S8 = 8,
	S9 = 9,
	S10 = 10,
	S11 = 11,
	S12 = 12,
	S13 = 13,
	S14 = 14,
	S15 = 15,
	S16 = 16,
	LEFT = S10,
	RIGHT = S12,
	UP = S7,
	DOWN = S15,
	CONFIRM = S6,
	CANCEL = S8,
	NB = 0
};
#endif /* GLOBALS_H_ */