/*
 * globals.h
 *
 * Created: 07.06.2015 10:18:59
 *  Author: TwoBit
 */ 


#ifndef GLOBALS_H_
#define GLOBALS_H_

#ifndef EXTERN
#define EXTERN extern
#endif 

EXTERN volatile uint8_t key;

enum KEYPAD_BUTTONS{
	S1 = 0,
	S2 = 1,
	S3 = 2,
	S4 = 3,
	S5 = 4,
	S6 = 5,
	S7 = 6,
	S8 = 7,
	S9 = 8,
	S10 = 9,
	S11 = 10,
	S12 = 11,
	S13 = 12,
	S14 = 13,
	S15 = 14,
	S16 = 15,
	LEFT = S10,
	RIGHT = S12,
	UP = S7,
	DOWN = S15,
	CONFIRM = S6,
	CANCEL = S8,
	NB = 255
};
#endif /* GLOBALS_H_ */