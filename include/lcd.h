#ifndef LCD
#define LCD

#include <stdlib.h>

#ifndef F_CPU
#define F_CPU 16000000UL 		// change this with respect to microcontroller clock speed.
#endif

#include <util/delay.h>
#include <avr/io.h>

#define DataBus				PORTD
#define DataDir_DataBus		DDRD

#define LCD_Control			PORTB
#define DataDir_LCD_Control	DDRB
#define RS					0		// pin numbers
#define ReadWrite			1
#define Enable				2

// 10Hz
void Initialize_LCD(void);	
void Check_if_LCD_is_busy(void);
void Flash_Enable(void);
void Send_Command(unsigned char command);
void Send_Character(unsigned char character);
void Send_String(char *stringOfCharacters);
void Send_Int(uint16_t var);
void Send_Double(double var, uint8_t width, uint8_t precision);
void GotoLCD_Location(uint8_t x, uint8_t y);

#endif
