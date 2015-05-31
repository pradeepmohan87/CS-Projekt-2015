/*
 * state_machine_main.c
 *
 * Created: 30.05.2015 19:50:53
 *  Author: TwoBit
 */ 

#include "../include/state_machine.h"

void SM_MAIN(void){
	
}	
void SM_PRINT(void){
	
}				
void SM_DEBOUNCE(uint8_t pin){
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
		case 150: {
			--counter;
			if(counter == 0)
			{
				state = 0;
			}
			break;
		}
	}	
}		
void SM_LCD(void){
	
}					