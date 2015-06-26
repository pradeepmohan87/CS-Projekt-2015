#ifndef LCD
#define LCD

#include <stdlib.h>

//#ifndef F_CPU
//#define F_CPU 16000000UL 	// change this with respect to microcontroller clock speed.
//#endif
//
//#include <util/delay.h>
//#include <avr/io.h>
#include "globals.h"

#define DataBus				PORTD
#define DataDir_DataBus		DDRD

#define LCD_Control			PORTB
#define DataDir_LCD_Control	DDRB
#define RS					0		// pin numbers
#define ReadWrite			1
#define Enable				2

// 10Hz or higher
void Initialize_LCD(void);	
void Check_if_LCD_is_busy(void);
void Flash_Enable(void);
void Clear_Screen(void);
void Send_Command(unsigned char command);
void Send_Character(unsigned char character);
void Send_String(char *stringOfCharacters);
void Send_Int(uint16_t var);
void Send_Double(double var, uint8_t width, uint8_t precision);
void GotoLCD_Location(uint8_t x, uint8_t y);

// Preprogrammed LCD Views:
void Show_Welcome(void);
void Show_Main_Menu(int page);
void Show_Print_Menu(int page);
void Show_Config_Menu(int page);
void Show_Print_LDR(void);
void Show_Print_Temp(void);
void Show_Cfg_Rate(void);
void Show_Cfg_LDR(void);
void Show_Cfg_Temp(void);
#endif
