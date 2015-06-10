/*
 * debouncer.c
 *
 * Created: 04.06.2015 15:15:42
 *  Author: TwoBit
 */ 

#include "../include/debouncer.h"
		
void DEBOUNCE_PORTA(uint8_t pin){
	volatile static int state = WAIT_FOR_BUTTON_ON;
	volatile static int counter = 0;
	
	switch(state)
	{
		case WAIT_FOR_BUTTON_ON: {
			if((PINA & pin) == 0){
				counter = 2;
				state = DEBOUNCING_BUTTON_ON;
			}
			break;
		}
		case DEBOUNCING_BUTTON_ON: {
			--counter;
			if(counter == 0)
			{
				state = WAIT_FOR_BUTTON_OFF;
			}
			break;
		}
		case WAIT_FOR_BUTTON_OFF: {
			if((PINA & pin) != 0)
			{
				counter = 2;
				state = DEBOUNCING_BUTTON_OFF;
			}
			break;
		}
		case DEBOUNCING_BUTTON_OFF: {
			--counter;
			if(counter == 0)
			{
				state = WAIT_FOR_BUTTON_ON;
			}
			break;
		}
	}	
}
