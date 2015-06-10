/*
 * state_machine_main.h
 *
 * Created: 30.05.2015 19:50:38
 *  Author: TwoBit
 */ 


#ifndef STATE_MACHINE_MAIN_H_
#define STATE_MACHINE_MAIN_H_

#include <avr/io.h>
#include "globals.h"
#include "lcd.h"

void MAIN_SM(void);		// 10kHz

enum MAIN_SM_STATES{
	MAIN_MENU = 0,
	PRINT_MENU = 50,
	CONFIG_MENU = 100,
	SET_TEMP_PARAM = 150,
	SET_LDR_PARAM = 200,
	SET_SAMPLE_RATE = 250,
	PRINT_TEMP = 300,
	PRINT_LDR = 350
};				

#endif /* STATE_MACHINE_MAIN_H_ */