/*
 * debouncer.h
 *
 * Created: 04.06.2015 15:14:57
 *  Author: TwoBit
 */ 


#ifndef DEBOUNCER_H_
#define DEBOUNCER_H_

#include "globals.h"

void DEBOUNCE_PORTA(uint8_t pin);	// 100Hz

enum BUTTON_STATES{
	WAIT_FOR_BUTTON_ON = 0,
	DEBOUNCING_BUTTON_ON = 50,
	WAIT_FOR_BUTTON_OFF = 100,
	DEBOUNCING_BUTTON_OFF =	150
};


#endif /* DEBOUNCER_H_ */