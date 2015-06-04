#include "../include/lcd.h"

char firstColumnPos[4] = {0, 64, 20, 84};

//***************************************************************************************************
void Initialize_LCD(){
	DataDir_LCD_Control |= (1<<Enable) | (1<<ReadWrite) | (1<<RS);
	_delay_ms(15);
	Send_Command(0x01);			// clear the screen
	_delay_ms(2);
	Send_Command(0x38);			// set for 8-bit mode
	_delay_us(50);
	Send_Command(0b00001100);	// screen: display on, cursor off, blink off
	_delay_us(50);
}
//***************************************************************************************************
void Check_if_LCD_is_busy(){
	DataDir_DataBus = 0;			// set for input
	LCD_Control |= (1<<ReadWrite);	// read from the LCD
	LCD_Control &= ~(1<<RS);		// set for command mode
	
		while(DataBus >=80)			// keep flashing Enable until the LCD is no longer busy
		{
		Flash_Enable();
		}

	DataDir_DataBus = 0xFF;			// set back to output
}
//***************************************************************************************************
void Flash_Enable(){
	LCD_Control |= (1<<Enable);
	asm volatile ("nop");
	asm volatile ("nop");
	LCD_Control &= ~(1<<Enable);
}
//***************************************************************************************************
void Send_Command(unsigned char command){
	Check_if_LCD_is_busy();
	DataBus = command;
	LCD_Control &= ~((1<<RS) | (1<<ReadWrite));
	Flash_Enable();
	DataBus = 0;
}
//***************************************************************************************************
void Send_Character(unsigned char character){
	Check_if_LCD_is_busy();
	DataBus = character;
	LCD_Control &= ~(1<<ReadWrite);
	LCD_Control |= (1<<RS);
	Flash_Enable();
	DataBus = 0;
}
//***************************************************************************************************
void Send_String(char *stringOfCharacters){
	while(*stringOfCharacters>0)
	{
	Send_Character(*stringOfCharacters++);
	}
}
//***************************************************************************************************
void Send_Int(uint16_t var){
	char var_as_string[6];			// string that will store the number
	itoa(var, var_as_string, 10);	// base: 2 for binary, 10 for decimal, 16 for hex
	Send_String(var_as_string);
}
//***************************************************************************************************
void Send_Double(double var, uint8_t width, uint8_t precision){	
	char var_as_string[width];							// string that will store the number
	dtostrf(var, width, precision, var_as_string);		// width: total length of the number incl decimals and sign
														// precision: the number of digits after decimal point
	Send_String(var_as_string);
}
//***************************************************************************************************
void GotoLCD_Location(uint8_t x, uint8_t y){
	Send_Command(0x80 + firstColumnPos[y-1] + (x-1));
}
//***************************************************************************************************
