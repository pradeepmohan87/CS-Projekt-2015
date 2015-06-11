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
				while(get_key() == UP) key = 0;		// Wait for Release!
				counter--;
				if(counter < 0) counter = 0;		
			}
			if(key == DOWN){
				while(get_key() == DOWN) key = 0;	// Wait for Release!
				counter++;
				if(counter > 2) counter = 2;
			}
			if(counter == 1 && key == CONFIRM){
				counter = 0;
				state = PRINT_MENU;
			}
			if(counter == 2 && key == CONFIRM){
				counter = 0;
				state = CONFIG_MENU;
			}
			break;
		}
		case PRINT_MENU: {
			Show_Print_Menu(counter);
			if(key == UP) {
				while(get_key() == UP) key = 0;		// Wait for Release!
				counter--;
				if(counter < 0) counter = 0;
			}
			if(key == DOWN){
				while(get_key() == DOWN) key = 0;	// Wait for Release!
				counter++;
				if(counter > 2) counter = 2;
			}
			if(counter == 1 && key == CONFIRM){ 
				counter = 0;
				state = PRINT_LDR;
			}
			if(counter == 2 && key == CONFIRM){
				counter = 0;
				state = PRINT_TEMP;
			}
			if(key == CANCEL){
				while(get_key() == CANCEL) key = 0; // Wait for Release!
				counter = 1;
				state = MAIN_MENU;
			}
			break;
		}
		case CONFIG_MENU: {
			Show_Config_Menu(counter);
			if(key == UP) {
				while(get_key() == UP) key = 0;		// Wait for Release!
				counter--;
				if(counter < 0) counter = 0;
			}
			if(key == DOWN){
				while(get_key() == DOWN) key = 0;	// Wait for Release!
				counter++;
				if(counter > 3) counter = 3;
			}
			if(counter == 1 && key == CONFIRM){
				counter = 0;
				state = SET_SAMPLE_RATE;
			}
			if(counter == 2 && key == CONFIRM){
				counter = 0;
				state = SET_LDR_PARAM;
			}
			if(counter == 3 && key == CONFIRM){
				counter = 0;
				state = SET_TEMP_PARAM;
			}
			if(key == CANCEL){
				while(get_key() == CANCEL) key = 0; // Wait for Release!
				counter = 2;
				state = MAIN_MENU;
			}
			break;
		}
		case PRINT_TEMP:
			Show_Print_Temp();
			if(key == CANCEL){
				while(get_key() == CANCEL) key = 0; // Wait for Release!
				counter = 2;
				state = PRINT_MENU;
			}
			break;
		case PRINT_LDR:
			Show_Print_LDR();
			if(key == CANCEL){
				while(get_key() == CANCEL) key = 0; // Wait for Release!
				counter = 1;
				state = PRINT_MENU;
			}
			break;
		case SET_SAMPLE_RATE:
			Show_Cfg_Rate();
			if(key == CANCEL){
				while(get_key() == CANCEL) key = 0; // Wait for Release!
				counter = 1;
				state = CONFIG_MENU;
			}
			break;
		case SET_LDR_PARAM:
			Show_Cfg_LDR();
			if(key == CANCEL){
				while(get_key() == CANCEL) key = 0; // Wait for Release!
				counter = 2;
				state = CONFIG_MENU;
			}
			break;
		case SET_TEMP_PARAM:
			Show_Cfg_Temp();
			if(key == CANCEL){
				while(get_key() == CANCEL) key = 0; // Wait for Release!
				counter = 3;
				state = CONFIG_MENU;
			}
			break;
	}
}		
				