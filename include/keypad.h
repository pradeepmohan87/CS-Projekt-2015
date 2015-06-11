/*
 * keypad.h
 *
 * Created: 04.06.2015 20:36:05
 *  Author: TwoBit
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_

#include <avr/io.h>
#include "globals.h"

#define KEYPAD_PORT PORTA
#define KEYPAD_DDR   DDRA
#define KEYPAD_PIN   PINA

uint8_t get_key(void);

//COL1 ->  PA7
//COL2 ->  PA6
//COL3 ->  PA5
//COL4 ->  PA4
//
//ROW1 ->  PA3
//ROW2 ->  PA2
//ROW3 ->  PA1
//ROW4 ->  PA0

#endif /* KEYPAD_H_ */