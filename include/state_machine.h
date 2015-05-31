/*
 * state_machine_main.h
 *
 * Created: 30.05.2015 19:50:38
 *  Author: TwoBit
 */ 


#ifndef STATE_MACHINE_MAIN_H_
#define STATE_MACHINE_MAIN_H_

#include <avr/io.h>

void SM_MAIN(void);					// 10kHz
void SM_PRINT(void);				// 1kHz
void SM_DEBOUNCE(uint8_t pin);		// 100Hz 
void SM_LCD(void);					// 10Hz

enum BUTTON_STATES{
	WAIT_FOR_BUTTON_ON = 0,
	DEBOUNCING_BUTTON_ON = 50,
	WAIT_FOR_BUTTON_OFF = 100,
	DEBOUNCING_BUTTON_OFF =	159
};


#endif /* STATE_MACHINE_MAIN_H_ */