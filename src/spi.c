/*
 * spi.c
 *
 * Created: 25.06.2015 01:35:15
 *  Author: Pradeep Mohan
 */ 

#include "../include/spi.h"


void setup_SPI()
{
 /*Setup SPI Pins */
  DDR_SPI |= (DATA | LATCH | CLOCK); 
  PORT_SPI &= ~(DATA |  CLOCK);        //Set data and clock pins low initially
  PORT_SPI |= LATCH; //Set Latch pin high initially
  
  SPCR = (1<<SPE) | (1<<MSTR) | (1<<SPR0);// | (1<<SPR0);  
  SPSR = (1<<SPI2X);
  /*
 SPI2X SPR1 SPR0 	SCK Frequency
	0		0		0			f/4
	0		0		1			f/16
	0		1		0			f/64
	0		1		1			f/128
	More options available, refer ATMEGA datasheet
	*/
  }
  
  void start_SPI()
  {
	SPCR |= (1<<SPE); //turning on the SPI before data transfer
	PORT_SPI |= (DATA | CLOCK);
	for(int bytecount=0;bytecount<48;bytecount++)
	{
		SPDR=0b00000000;
		while(!(SPSR & (1<<SPIF)));
	}
  }
  
  void stop_SPI()
  {
	  SPCR &= ~(1<<SPE); //turning off the SPI after data transfer
	  PORT_SPI &= ~(DATA | CLOCK);
  }
  
  void send_single_line_via_SPI(char single_line[48])
  {
	  int bytecount=0;
	  for( bytecount=0;bytecount<48;bytecount++)
	  {
		  SPDR=single_line[bytecount];
		  while(!(SPSR & (1<<SPIF)));

	  }
  }