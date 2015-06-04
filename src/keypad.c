/*
 * keypad.c
 *
 * Created: 04.06.2015 20:36:43
 *  Author: TwoBit
 */ 

#include "../include/keypad.h"

uint8_t getKey()
{
	uint8_t r,c;

	KEYPAD_PORT |= 0x0F;

	for(c=0;c<4;c++)
	{
		KEYPAD_DDR &=~ (0xFF);

		KEYPAD_DDR |= (0x80>>c);
		for(r=0;r<4;r++)
		{
			if(!(KEYPAD_PIN & (0X08>>r)))
			{
				return (r*4+c);
			}
		}
	}

	return 0XFF;//Indicate No key pressed
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