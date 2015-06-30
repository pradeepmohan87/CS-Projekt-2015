/*
 * state_machine_main.h
 *
 * Created: 30.05.2015 19:50:38
 *  Author: TwoBit
 */ 


#ifndef STATE_MACHINE_MAIN_H_
#define STATE_MACHINE_MAIN_H_

#include "globals.h"
#include "lcd.h"

void MAIN_STATEMACHINE(void);		// 10kHz

enum MAIN_SM_STATES{
	MAIN_MENU = 0,
	PRINT_MENU = 50,
	CONFIG_MENU = 100,
	SET_SAMPLE_RATE = 150,
	SET_LDR_PARAM_FROM = 250,
	SET_LDR_PARAM_TO = 300,
	SET_TEMP_PARAM_FROM = 400,
	SET_TEMP_PARAM_TO = 450,	
	PRINT_TEMP = 500,
	PRINT_LDR = 550
};				

#endif /* STATE_MACHINE_MAIN_H_ */