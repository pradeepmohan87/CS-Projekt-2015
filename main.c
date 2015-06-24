/*
 * TCR.c
 *
 * Created: 30.05.2015 15:43:36
 *  Author: TwoBit
 */ 
#include "include/globals.h"
#include "include/timer.h"
#include "include/adc.h"
#include "include/state_machine.h"
#include "include/lcd.h"
#include "include/debouncer.h"
#include "include/printer.h"
#include "include/keypad.h"

// Init Functions:
void port_init(void);

// Timer-Slicer Interrupts:
void int1Hz(void);
void int10Hz(void);
void int100Hz(void);
void int1kHz(void);
void int10kHz(void);

int main(void)
{
	// Initialize System
	Initialize_LCD();
	timer_init();
	port_init();
	keypad_init();
	adc_init();
	
	//Welcome Screen
	Show_Welcome();
	_delay_ms(200);
	sei();	
	while(1)
	{
    }
}

void port_init(void){
	DDRC = 0xFF;	// LED Output
}
//void int1Hz(void){
	//PORTC ^= (1<<PC0);	
//}
//void int10Hz(void){	
	//PORTC ^= (1<<PC1);
//}
//void int100Hz(void){ //28Hz
	//PORTC ^= (1<<PC2);
//}
//void int1kHz(void){ // 50us CycleTime and Deley of 6ms
	//PORTC ^= (1<<PC3); 
	//key = get_key();
	//PORTC = key;	
//}
void int10kHz(void){ // 1.5khz but with hard Jittering	
	key = get_key();
	PORTC = key;
	MAIN_STATEMACHINE();
}