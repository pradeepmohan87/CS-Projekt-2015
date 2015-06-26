/*
 * spi.h
 *
 * Created: 25.06.2015 01:35:15
 *  Author: Pradeep Mohan
 */ 

#ifndef SPI_H_
#define SPI_H_


#include "globals.h"

#define DDR_SPI DDRB
#define PORT_SPI PORTB

#define LATCH (1<<PINB3)        //SS   (RCK) 10
#define DATA (1<<PINB5)     //MOSI (SI) 11
#define CLOCK (1<<PINB7)



void setup_SPI();
void start_SPI();
void stop_SPI();
void send_single_line_via_SPI(char single_line[48]);

#endif /* SPI_H_ */