/*
 * TCR.c
 *
 * Created: 30.05.2015 15:43:36
 *  Author: TwoBit
 */ 

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>

#include "include/timer.h"
#include "include/adc.h"
#include "include/state_machine.h"
#include "include/lcd.h"
#include "include/debouncer.h"
#include "include/printer.h"
#include "include/keypad.h"


void port_init(void);
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
	sei();
	
	// Welcome Screen
	GotoLCD_Location(1,1);
	Send_String("Thermal Chart");
		
	GotoLCD_Location(1,2);
	Send_String("Recorder");
	
	uint8_t key;
    while(1)
    {
		key = getKey();
		GotoLCD_Location(10,2);
		Send_Int(key);
    }
}

void port_init(void){
	DDRC = 0xFF;	// LED Output
	DDRA = 0xFF;
}
void int1Hz(void){
	//PORTC ^= (1<<PC0);
}
void int10Hz(void){
	//PORTC ^= (1<<PC1);
}
void int100Hz(void){
	//PORTC ^= (1<<PC2);
}
void int1kHz(void){
	//PORTC ^= (1<<PC3);
}
void int10kHz(void){
	//PORTC ^= (1<<PC4);
}