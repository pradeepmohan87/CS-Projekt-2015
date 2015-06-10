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

uint8_t getKey(void);
uint8_t GetKeyPressed(void);
//uint8_t getKeypad(void);



#endif /* KEYPAD_H_ */