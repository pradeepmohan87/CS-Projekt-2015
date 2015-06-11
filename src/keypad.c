/*
 * keypad.c
 *
 * Created: 04.06.2015 20:36:43
 *  Author: TwoBit
 */ 
#include "../include/keypad.h"

uint8_t get_key(void){
	//first column
	PORTA= 0b01111111;
	if (!bit_is_set(PINA, 3)) return 4;
	if (!bit_is_set(PINA, 2)) return 5;
	if (!bit_is_set(PINA, 1)) return 9;
	if (!bit_is_set(PINA, 0)) return 13;

	//second column
	PORTA =0b10111111;
	if (!bit_is_set(PINA, 3)) return 1;
	if (!bit_is_set(PINA, 2)) return 6;
	if (!bit_is_set(PINA, 1)) return 10;
	if (!bit_is_set(PINA, 0)) return 14;

	//third column
	PORTA =0b11011111;
	if (!bit_is_set(PINA, 3)) return 2;
	if (!bit_is_set(PINA, 2)) return 7;
	if (!bit_is_set(PINA, 1)) return 11;
	if (!bit_is_set(PINA, 0)) return 15;

	//fourth column
	PORTA =0b11101111;
	if (!bit_is_set(PINA, 3)) return 3;
	if (!bit_is_set(PINA, 2)) return 8;
	if (!bit_is_set(PINA, 1)) return 12;
	if (!bit_is_set(PINA, 0)) return 16;
	
	return 0;
}