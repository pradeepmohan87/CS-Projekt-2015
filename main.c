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

#define EXTERN
#include "include/globals.h"

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
	
	//Welcome Screen
	Show_Welcome();
	_delay_ms(200);
	Clear_Screen();
	
	sei();	
	while(1)
	{
		
    }
}

void port_init(void){
	DDRC = 0xFF;	// LED Output
	
	// PA0-PA3 = Input    (R1-R4)
	// PA4-PA7 = H Resist (C1-C4)
	
	DDRA = 0xF0;	// H nibble for output(columns) L for input(rows);
	PORTA = 0x0F;	// Activate int. Pullups
}
void int1Hz(void){
}
void int10Hz(void){
}
void int100Hz(void){

}
void int1kHz(void){
	PORTC = 0x00;
	key = get_key();
	PORTC = key;
}
void int10kHz(void){
	MAIN_SM();
}