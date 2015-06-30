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
void Clear_Screen(void){
		GotoLCD_Location(1,1);
		Send_String("                ");
		GotoLCD_Location(1,2);
		Send_String("                ");
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
void Show_Welcome(void){
	GotoLCD_Location(1,1);
	Send_String("Thermal Chart");
	GotoLCD_Location(1,2);
	Send_String("Recorder");
}
void Show_Main_Menu(int page){
	switch (page)
	{
	case 0:
		GotoLCD_Location(1,1);
		Send_String("    Main Menu   ");
		GotoLCD_Location(1,2);
		Send_String("S7 Up | S15 Down");	
		break;
	case 1:
		GotoLCD_Location(1,1);
		Send_String("Do a measurement");
		GotoLCD_Location(1,2);
		Send_String("S6 OK  |        ");
		break;
	case 2:
		GotoLCD_Location(1,1);
		Send_String("Configuration   ");
		GotoLCD_Location(1,2);
		Send_String("S6 OK  |        ");
		break;
	}
}
void Show_Print_Menu(int page){
	switch (page)
	{
	case 0:
		GotoLCD_Location(1,1);
		Send_String("   Print Menu   ");
		GotoLCD_Location(1,2);
		Send_String("       |  S8 CAN");
		break;
	case 1:
		GotoLCD_Location(1,1);
		Send_String("Measure LDR     ");
		GotoLCD_Location(1,2);
		Send_String("S6 OK  |  S8 CAN");
		break;
	case 2:
		GotoLCD_Location(1,1);
		Send_String("Measure Temp    ");
		GotoLCD_Location(1,2);
		Send_String("S6 OK  |  S8 CAN");
		break;
	}	
}
void Show_Print_LDR(void){
	GotoLCD_Location(1,1);
	Send_String("Printing LDR    ");
	GotoLCD_Location(1,2);
	Send_String("       |  S8 CAN");
}
void Show_Print_Temp(void){
	GotoLCD_Location(1,1);
	Send_String("Printing Temp   ");
	GotoLCD_Location(1,2);
	Send_String("       |  S8 CAN");
}

void Show_Config_Menu(int page){
	switch (page)
	{
	case 0:
		GotoLCD_Location(1,1);
		Send_String("   Config Menu  ");
		GotoLCD_Location(1,2);
		Send_String("       |  S8 CAN");
		break;
	case 1:
		GotoLCD_Location(1,1);
		Send_String("Set Sample Rate ");
		GotoLCD_Location(1,2);
		Send_String("S6 OK  |  S8 CAN");
		break;
	case 2:
		GotoLCD_Location(1,1);
		Send_String("Set LDR range   ");
		GotoLCD_Location(1,2);
		Send_String("S6 OK  |  S8 CAN");
		break;
	case 3:
		GotoLCD_Location(1,1);
		Send_String("Set Temp range  ");
		GotoLCD_Location(1,2);
		Send_String("S6 OK  |  S8 CAN");
		break;
	}
}
/************* SAMPLE RATE *****************/
void Show_Cfg_Rate(void){
	GotoLCD_Location(1,1);
	Send_String("Samples/s:      ");
	GotoLCD_Location(12,1);
	Send_Double(500/sample_rate,3,1);
	GotoLCD_Location(1,2);
	Send_String("S7|S15 |  S8 OK ");
}
/************* LDR *****************/
void Show_Cfg_LDR(void){
	GotoLCD_Location(1,1);
	Send_String("Set LDR %1      ");
	GotoLCD_Location(1,2);
	Send_String("S7|S15 |  S8 OK ");
}
void Show_LDR_From(void){
	GotoLCD_Location(1,1);
	Send_String("Light from:     ");
	
	GotoLCD_Location(12,1);
	Send_Int(range_min);
	
	GotoLCD_Location(1,2);
	Send_String("S7|S15 |  S8 OK ");
}
void Show_LDR_To(void){
	GotoLCD_Location(1,1);
	Send_String("Light to:       ");
	
	GotoLCD_Location(10,1);
	Send_Int(range_max);
	
	GotoLCD_Location(1,2);
	Send_String("S7|S15 |  S8 OK ");
}


/************* TEMP *****************/
void Show_Cfg_Temp(void){
	GotoLCD_Location(1,1);
	Send_String("Set Temp %1     ");
	GotoLCD_Location(1,2);
	Send_String("S7|S15 |  S8 OK ");
}
void Show_Temp_From(void){
	GotoLCD_Location(1,1);
	Send_String("Temp. from:     ");
	GotoLCD_Location(12,1);
	Send_Int(temp_min);
	GotoLCD_Location(1,2);
	Send_String("S7|S15 |  S8 OK ");
}
void Show_Temp_To(void){
	GotoLCD_Location(1,1);
	Send_String("Temp. to:       ");
	GotoLCD_Location(10,1);
	Send_Int(temp_max);
	GotoLCD_Location(1,2);
	Send_String("S7|S15 |  S8 OK ");
}
