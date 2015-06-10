/*
 * keypad.c
 *
 * Created: 04.06.2015 20:36:43
 *  Author: TwoBit
 */ 
#include "../include/keypad.h"

uint8_t getKey()
{
	uint8_t row,col;
	
	KEYPAD_PORT |= 0x0F;
	
	for(col=0;col<4;col++)
	{
		KEYPAD_DDR &=~ (0xFF);
		KEYPAD_DDR |= (0x80>>col);
		
		for(row=0;row<4;row++)
		{
			if(!(KEYPAD_PIN & (0x08>>row)))
			{
				return (row*4+col);
			}
		}
	}
	return 255;//Indicate No key pressed
}
uint8_t GetKeyPressed(void)
{
	uint8_t r,c;
	
	KEYPAD_PORT|= 0X0F;
	
	for(c=0;c<3;c++)
	{
		KEYPAD_DDR&=~(0X7F);
		KEYPAD_DDR|=(0X40>>c);
		for(r=0;r<4;r++)
		{
			if(!(KEYPAD_PIN & (0X08>>r)))
			{
				return (r*3+c);
			}
		}
	}
	return 0XFF;//Indicate No key pressed
}
//uint8_t getKeypad(void){
	////first column
	//PORTA =0b01111111;
	//if (bit_is_set(PINA, 3)) return 1;
	//if (bit_is_set(PINA, 2)) return 2;
	//if (bit_is_set(PINA, 1)) return 3;
	//if (bit_is_set(PINA, 0)) return 4;
//
	////second column
	//PORTA =0b10111111;
	//if (bit_is_set(PINA, 3)) return 5;
	//if (bit_is_set(PINA, 2)) return 6;
	//if (bit_is_set(PINA, 1)) return 7;
	//if (bit_is_set(PINA, 0)) return 8;
//
	////third column
	//PORTA =0b11011111;
	//if (bit_is_set(PINA, 3)) return 9;
	//if (bit_is_set(PINA, 2)) return 10;
	//if (bit_is_set(PINA, 1)) return 11;
	//if (bit_is_set(PINA, 0)) return 12;
//
	////fourth column
	//PORTA =0b11101111;
	//if (bit_is_set(PINA, 3)) return 13;
	//if (bit_is_set(PINA, 2)) return 14;
	//if (bit_is_set(PINA, 1)) return 15;
	//if (bit_is_set(PINA, 0)) return 16;
	//
	//return 0;
//}