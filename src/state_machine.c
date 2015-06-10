/*
 * state_machine_main.c
 *
 * Created: 30.05.2015 19:50:53
 *  Author: TwoBit
 */ 

#include "../include/state_machine.h"
#include "../include/keypad.h"

void MAIN_SM(void){
	volatile static int state = MAIN_MENU;
	volatile static int counter = 0;
	
	switch(state)
	{
		case MAIN_MENU: {
			Show_Main_Menu(counter);
			if(key == UP) {
				while(getKey() == UP);	// Wait for Release!
				counter--;
				Clear_Screen();
				if(counter < 0) counter = 0;		
			}
			if(key == DOWN){
				while(getKey() == DOWN); // Wait for Release!
				counter++;
				Clear_Screen();
				if(counter > 2) counter = 2;
			}
			if(counter == 1 && key == CONFIRM){
				counter = 0;
				Clear_Screen();
				state = PRINT_MENU;
			}
			if(counter == 2 && key == CONFIRM){
				counter = 0;
				Clear_Screen();
				state = CONFIG_MENU;
			}
			break;
		}
		case PRINT_MENU: {
			PORTC |= (1<<PC0);
			if(key == UP) counter++;
			if(key == DOWN) counter--;
			if(counter == 1 && key == CONFIRM){ 
				counter = 0;
				state = PRINT_LDR;
			}
			if(counter == 2 && key == CONFIRM){
				counter = 0;
				state = PRINT_LDR;
			}
			if(key == CANCEL){
				counter = 0;
				state = MAIN_MENU;
			}
			break;
		}
		case CONFIG_MENU: {
			PORTC |= (1<<PC1);
			if(key == UP) counter++;
			if(key == DOWN) counter--;
			if(counter == 1 && key == CONFIRM){
				counter = 0;
				state = SET_SAMPLE_RATE;
			}
			if(counter == 2 && key == CONFIRM){
				counter = 0;
				state = SET_LDR_PARAM;
			}
			if(key == CANCEL){
				counter = 0;
				state = SET_TEMP_PARAM;
			}
			break;
		}
		case PRINT_TEMP:
			break;
		case PRINT_LDR:
			break;
		case SET_SAMPLE_RATE:
			break;
		case SET_LDR_PARAM:
			break;
		case SET_TEMP_PARAM:
			break;
	}
}		
				