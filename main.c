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
#include "include/spi.h"
#include "include/keypad.h"
#include "include/ds18x20lib.h"
#include <stdio.h>

// Timer-Slicer Interrupts:
void int1Hz(void);
void int10Hz(void);
void int100Hz(void);
void int1kHz(void);
void int10kHz(void);

// Measurmet Values:
volatile int8_t temp = 0;
volatile uint16_t ldr_value = 0;

// Config Parameter Default Definitions:
volatile int sample_rate = 50;

volatile int range_min = 0;
volatile int range_max = 1000;

volatile int temp_min = 0;
volatile int temp_max = 125;

float temperature;

unsigned char temp_po_str[8];
float temp_po;

int main(void)
{
	// Initialize System
	Initialize_LCD();
	timer0_init();
	timer1_init();
	init_printer();
	setup_strobes();
	setup_SPI();
	keypad_init();
	adc_init();
	ds1820_init(USEDPIN);              //Initialize DS1820 Buffer oben
		
	//Welcome Screen
	Show_Welcome();
	_delay_ms(100);
	Clear_Screen();
	
	sei();	
	
	while(1)
	{
    }
}

// Timer-Slicer Interrupts Definitions:
void int10kHz(void){ // Critical Section
	key = get_key();
	MAIN_STATEMACHINE();
}