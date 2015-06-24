/*
 * state_machine_main.c
 *
 * Created: 30.05.2015 19:50:53
 *  Author: TwoBit
 */ 

#include "../include/state_machine.h"
#include "../include/keypad.h"
#include "../include/adc.h"

enum Boolean{
	false = 0,
	true = 1
};

void MAIN_STATEMACHINE(void){
	volatile static int state = MAIN_MENU;
	volatile static int counter = 0;
	volatile static int sema_flag = true;
	
	switch(state)
	{
		case MAIN_MENU: {
			if(sema_flag){	// Print LCD once
				Show_Main_Menu(counter);
				sema_flag = false;
			}
			if(key == UP) {
				while(get_key() == UP) key = 0;		// Wait for Release!
				counter--;
				sema_flag = true; // Allow LCD to print
				if(counter < 0) counter = 0;		
			}
			if(key == DOWN){
				while(get_key() == DOWN) key = 0;	// Wait for Release!
				counter++;
				sema_flag = true; // Allow LCD to print
				if(counter > 2) counter = 2;
			}
			if(counter == 1 && key == CONFIRM){
				counter = 0;
				sema_flag = true; // Allow LCD to print
				state = PRINT_MENU;
			}
			if(counter == 2 && key == CONFIRM){
				counter = 0;
				sema_flag = true; // Allow LCD to print
				state = CONFIG_MENU;
			}
			break;
		}
		case PRINT_MENU: {
			if(sema_flag){	// Print LCD once
				Show_Print_Menu(counter);
				sema_flag = false;
			}
			if(key == UP) {
				while(get_key() == UP) key = 0;		// Wait for Release!
				counter--;
				sema_flag = true; // Allow LCD to print
				if(counter < 0) counter = 0;
			}
			if(key == DOWN){
				while(get_key() == DOWN) key = 0;	// Wait for Release!
				counter++;
				sema_flag = true; // Allow LCD to print
				if(counter > 2) counter = 2;
			}
			if(counter == 1 && key == CONFIRM){ 
				counter = 0;
				sema_flag = true; // Allow LCD to print
				state = PRINT_LDR;
			}
			if(counter == 2 && key == CONFIRM){
				counter = 0;
				sema_flag = true; // Allow LCD to print
				state = PRINT_TEMP;
			}
			if(key == CANCEL){
				while(get_key() == CANCEL) key = 0; // Wait for Release!
				counter = 1;
				sema_flag = true; // Allow LCD to print
				state = MAIN_MENU;
			}
			break;
		}
		case CONFIG_MENU: {
			if(sema_flag){	// Print LCD once
				Show_Config_Menu(counter);
				sema_flag = false;
			}
			if(key == UP) {
				while(get_key() == UP) key = 0;		// Wait for Release!
				counter--;
				sema_flag = true; // Allow LCD to print
				if(counter < 0) counter = 0;
			}
			if(key == DOWN){
				while(get_key() == DOWN) key = 0;	// Wait for Release!
				counter++;
				sema_flag = true; // Allow LCD to print
				if(counter > 3) counter = 3;
			}
			if(counter == 1 && key == CONFIRM){
				counter = 0;
				sema_flag = true; // Allow LCD to print
				state = SET_SAMPLE_RATE;
			}
			if(counter == 2 && key == CONFIRM){
				counter = 0;
				sema_flag = true; // Allow LCD to print
				state = SET_LDR_PARAM;
			}
			if(counter == 3 && key == CONFIRM){
				counter = 0;
				sema_flag = true; // Allow LCD to print
				state = SET_TEMP_PARAM;
			}
			if(key == CANCEL){
				while(get_key() == CANCEL) key = 0; // Wait for Release!
				counter = 2;
				sema_flag = true; // Allow LCD to print
				state = MAIN_MENU;
			}
			break;
		}
		case PRINT_TEMP:{
			if(sema_flag){	// Print LCD once
				Show_Print_Temp();
				sema_flag = false;
			}
			if(key == CANCEL){
				while(get_key() == CANCEL) key = 0; // Wait for Release!
				counter = 2;
				sema_flag = true; // Allow LCD to print
				state = PRINT_MENU; 
			}
			break;
		}
		case PRINT_LDR:{
			if(sema_flag){	// Print LCD once
				Show_Print_LDR();
				sema_flag = false;
			}
			if(key == CANCEL){
				while(get_key() == CANCEL) key = 0; // Wait for Release!
				counter = 1;
				sema_flag = true; // Allow LCD to print
				state = PRINT_MENU;
			}
			uint16_t adc_value = adc_get(3);
			_delay_ms(10);
			
			GotoLCD_Location(1,1);
			Send_String("ADC VALUE:      ");
			
			GotoLCD_Location(12,1);
			Send_Int(adc_value);
			
			GotoLCD_Location(1,2);
			Send_String("       |  S8 CAN");
			
			break;
		}
		case SET_SAMPLE_RATE:{
			if(sema_flag){	// Print LCD once
				Show_Cfg_Rate();
				sema_flag = false;
			}
			if(key == CANCEL){
				while(get_key() == CANCEL) key = 0; // Wait for Release!
				counter = 1;
				sema_flag = true; // Allow LCD to print
				state = CONFIG_MENU;
			}
			break;
		}
		case SET_LDR_PARAM:{
			if(sema_flag){	// Print LCD once
				Show_Cfg_LDR();
				sema_flag = false;
			}

			if(key == CANCEL){
				while(get_key() == CANCEL) key = 0; // Wait for Release!
				counter = 2;
				sema_flag = true; // Allow LCD to print
				state = CONFIG_MENU;
			}
			break;
		}
		case SET_TEMP_PARAM:{
			if(sema_flag){	// Print LCD once
				Show_Cfg_Temp();
				sema_flag = false;
			}
			if(key == CANCEL){
				while(get_key() == CANCEL) key = 0; // Wait for Release!
				counter = 3;
				sema_flag = true; // Allow LCD to print
				state = CONFIG_MENU;
			}
			break;
		}
	}
}		
				