/*
 * keypad.c
 *
 * Created: 04.06.2015 20:36:43
 *  Author: TwoBit
 */ 
#include "../include/keypad.h"


void keypad_init(void){
	// PA0-PA3 = Input    (R1-R4)
	// PA4-PA7 = H Resist (C1-C4)
	DDRA = 0x70;	// H nibble for output(columns) L for input(rows);
	PORTA = 0x0F;	// Activate int. Pullups
}

uint8_t get_key(void){
	// To reduce the Pin-Usage only column 2 to 4 is sampled
	// PA3 and PA7 are used for ADC conversion
	 
	//second column
	PORTA =0b00110111;
	if (!bit_is_set(PINA, 3)) return 1;
	if (!bit_is_set(PINA, 2)) return 6;
	if (!bit_is_set(PINA, 1)) return 10;
	if (!bit_is_set(PINA, 0)) return 14;
	
	//third column
	PORTA =0b01010111;
	if (!bit_is_set(PINA, 3)) return 2;
	if (!bit_is_set(PINA, 2)) return 7;
	if (!bit_is_set(PINA, 1)) return 11;
	if (!bit_is_set(PINA, 0)) return 15;
	
	//fourth column
	PORTA =0b01100111;
	if (!bit_is_set(PINA, 3)) return 3;
	if (!bit_is_set(PINA, 2)) return 8;
	if (!bit_is_set(PINA, 1)) return 12;
	if (!bit_is_set(PINA, 0)) return 16;
	
	return 0;
}