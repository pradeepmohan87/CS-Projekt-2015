/*
 * printer.h
 *
 * Created: 25.06.2015 01:05:05
 *  Author: Pradeep Mohan
 */ 
#ifndef PRINTER_H_
#define PRINTER_H_


#include "globals.h"



#define MSTEP_PIN (1<<PINB6) //9
#define MDIR_PIN (1<<PINB4) //8

#define DDR_MOTOR DDRB
#define PORT_MOTOR PORTB


#define DDR_STROBE DDRC
#define PORT_STROBE PORTC


#define STROBE1 (1<<PINC1)
#define STROBE2 (1<<PINC2)
#define STROBE3 (1<<PINC3)
#define STROBE4 (1<<PINC4)
#define STROBE5 (1<<PINC5)
#define STROBE6 (1<<PINC6)


void setup_strobes();
void print_buffer_divided();
void init_printer();
void print_temp(uint16_t tempreading);
void data_write_temp(uint16_t tempreading);
long int map_temp(long int xtemp, long int in_min, long int in_max, long int out_min, long int out_max);
void stop_sm();
void paper_rewind(int num_lines);
void paper_out(int num_lines);
void data_write_yaxis();
void data_write_buffer_str(char *stringOfCharacters);
void data_write_buffer_char(char c);
void data_write_buffer_char_vertical(char c);

#endif /* PRINTER_H_ */