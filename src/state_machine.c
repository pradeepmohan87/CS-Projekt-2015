/*
 * state_machine_main.c
 *
 * Created: 30.05.2015 19:50:53
 *  Author: TwoBit
 */ 

#include "../include/state_machine.h"
#include "../include/keypad.h"
#include "../include/adc.h"
#include "../include/ds18x20lib.h"

enum Boolean{
	false = 0,
	true = 1
};

void MAIN_STATEMACHINE(void){
	volatile static int state = MAIN_MENU;
	volatile static int counter = 0;
	volatile static int sema_flag = true;
	const static int8_t t_debounce = 20;
	
	switch(state)
	{
		case MAIN_MENU: {
			if(sema_flag){	// Print LCD once
				Show_Main_Menu(counter);
				sema_flag = false;
			}
			if(key == UP) {
				_delay_ms(t_debounce);
				while(get_key() == UP){
					key = 0; // Wait for Release!
				}
				counter--;
				sema_flag = true; // Allow LCD to print
				if(counter < 0) counter = 0;		
			}
			if(key == DOWN){
				_delay_ms(t_debounce);
				while(get_key() == DOWN){
					key = 0; // Wait for Release!
				}
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
				_delay_ms(t_debounce);
				while(get_key() == UP){
					key = 0; // Wait for Release!
				}
				counter--;
				sema_flag = true; // Allow LCD to print
				if(counter < 0) counter = 0;
			}
			if(key == DOWN){
				_delay_ms(t_debounce);
				while(get_key() == DOWN){
					key = 0; // Wait for Release!
				}
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
				_delay_ms(t_debounce);
				while(get_key() == CANCEL){
					key = 0; // Wait for Release!
				}
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
				_delay_ms(t_debounce);
				while(get_key() == UP){
					key = 0; // Wait for Release!
				}
				counter--;
				sema_flag = true; // Allow LCD to print
				if(counter < 0) counter = 0;
			}
			if(key == DOWN){
				_delay_ms(t_debounce);
				while(get_key() == DOWN){
					key = 0; // Wait for Release!
				}
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
				state = SET_LDR_PARAM_FROM;
			}
			if(counter == 3 && key == CONFIRM){
				counter = 0;
				sema_flag = true; // Allow LCD to print
				state = SET_TEMP_PARAM_FROM;
			}
			if(key == CANCEL){
				_delay_ms(t_debounce);
				while(get_key() == CANCEL){
					key = 0; // Wait for Release!
				}
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
				_delay_ms(t_debounce);
				while(get_key() == CANCEL) {
					key = 0; // Wait for Release!
				}
				counter = 2;
				sema_flag = true; // Allow LCD to print
				state = PRINT_MENU; 
				print_graph=20;
			}
			// Print DS1820 Values
			print_temp_flag=1;
			if(!print_graph) print_graph=1;
			if(print_graph==10){
				temp = ds1820_read_temp(USEDPIN);//Get temperature from DS1820 puffer oben
			}
			break;
		}
		case PRINT_LDR:{
			if(sema_flag){	// Print LCD once
				Show_Print_LDR();
				sema_flag = false;
			}
			if(key == CANCEL){
				_delay_ms(t_debounce);
				while(get_key() == CANCEL){
					key = 0; // Wait for Release!
				}
				counter = 1;
				sema_flag = true; // Allow LCD to print
				state = PRINT_MENU;
				print_graph=20;
			}
			// Print LDR Values
			ldr_value = adc_get(3);			
			print_temp_flag=0;
			if(!print_graph) print_graph=1;	
			if(print_graph==10) { //get ADC value only if values have started printing
			}
			break;
		}
		case SET_SAMPLE_RATE:{
			if(sema_flag){	// Print LCD once
				Show_Cfg_Rate();
				sema_flag = false;
			}
			if(key == UP) {
				_delay_ms(t_debounce);
				sample_rate = sample_rate - 10;
				sema_flag = true; // Allow LCD to print
				if(sample_rate < 50) sample_rate = 50;
			}
			if(key == DOWN){
				_delay_ms(t_debounce);
				sample_rate = sample_rate + 10;
				sema_flag = true; // Allow LCD to print
				if(sample_rate > 500) sample_rate = 500;
			}
			if(key == CANCEL){
				_delay_ms(t_debounce);
				while(get_key() == CANCEL){
					 key = 0; // Wait for Release!
				}
				counter = 1;
				sema_flag = true; // Allow LCD to print
				state = CONFIG_MENU;
			}
			break;
		}
		case SET_LDR_PARAM_FROM:{
			if(sema_flag){	// Print LCD once
				Show_LDR_From();
				sema_flag = false;
			}
			if(key == UP) {
				_delay_ms(t_debounce);
				range_min++;
				sema_flag = true; // Allow LCD to print
				if(range_min > 1023) range_min = 1023;
			}
			if(key == DOWN){
				_delay_ms(t_debounce);
				range_min--;
				sema_flag = true; // Allow LCD to print
				if(range_min < 0) range_min = 0;
			}
			if(key == CANCEL){
				_delay_ms(t_debounce);
				while(get_key() == CANCEL){
					key = 0; // Wait for Release!
				}
				sema_flag = true; // Allow LCD to print
				state = SET_LDR_PARAM_TO;
			}
			break;
		}
		case SET_LDR_PARAM_TO:{
			if(sema_flag){	// Print LCD once
				Show_LDR_To();
				sema_flag = false;
			}
			if(key == UP) {
				_delay_ms(t_debounce);
				range_max++;
				sema_flag = true; // Allow LCD to print
				if(range_max > 1023) range_max = 1023;
			}
			if(key == DOWN){
				_delay_ms(t_debounce);
				range_max--;
				sema_flag = true; // Allow LCD to print
				if(range_max < 0) range_max = 0;
			}
			if(key == CANCEL){
				_delay_ms(t_debounce);
				while(get_key() == CANCEL){
					key = 0; // Wait for Release!
				}
				counter = 2;
				sema_flag = true; // Allow LCD to print
				state = CONFIG_MENU;
			}
			break;
		}
		case SET_TEMP_PARAM_FROM:{
			if(sema_flag){	// Print LCD once
				Show_Temp_From();
				sema_flag = false;
			}
			if(key == UP) {
				_delay_ms(t_debounce);
				temp_min++;
				sema_flag = true; // Allow LCD to print
				if(temp_min > 125) temp_min = 125;
			}
			if(key == DOWN){
				_delay_ms(t_debounce);
				temp_min--;
				sema_flag = true; // Allow LCD to print
				if(temp_min < -55) temp_min = -55;
			}
			if(key == CANCEL){
				_delay_ms(t_debounce);
				while(get_key() == CANCEL){
					key = 0; // Wait for Release!
				}
				sema_flag = true; // Allow LCD to print
				state = SET_TEMP_PARAM_TO;
			}
			break;
		}
		case SET_TEMP_PARAM_TO:{
			if(sema_flag){	// Print LCD once
				Show_Temp_To();
				sema_flag = false;
			}
			if(key == UP) {
				_delay_ms(t_debounce);
				temp_max++;
				sema_flag = true; // Allow LCD to print
				if(temp_max > 125) temp_max = 125;
			}
			if(key == DOWN){
				_delay_ms(t_debounce);
				temp_max--;
				sema_flag = true; // Allow LCD to print
				if(temp_max < -40) temp_max = -40;
			}
			if(key == CANCEL){
				_delay_ms(t_debounce);
				while(get_key() == CANCEL){
					key = 0; // Wait for Release!
				}
				counter = 3;
				sema_flag = true; // Allow LCD to print
				state = CONFIG_MENU;
			}
			break;
		}
	}
}		
				