
#include <avr/io.h>
#include <math.h>
#include <util/delay.h>

#ifndef _DS18X20LIB_h_
#define _DS18X20LIB_h_

//-----------------------------------------
// Set Ports
//-----------------------------------------
#define USEDPIN		PC0					   //DS1820 PIN NB
#define DS1820_PIN	PINC                   //DS1820 PIN
#define DS1820_PORT	PORTC                  //DS1820 PORT
#define DS1820_DDR	DDRC                   //DS1820 DDR
//-----------------------------------------
// Prototypes
//-----------------------------------------
uint8_t	ds1820_reset(uint8_t);
void	ds1820_wr_bit(uint8_t,uint8_t);
uint8_t ds1820_re_bit(uint8_t);
uint8_t ds1820_re_byte(uint8_t);
void	ds1820_wr_byte(uint8_t,uint8_t);
float	ds1820_read_temp(uint8_t);
void	ds1820_init(uint8_t);

#endif
