/*
 * printer.c
 *
 * Created: 24.06.2015 15:43:16
 *  Author: Pradeep Mohan
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>

#include "../include/timer.h"
#include "../include/printer.h"
#include "../include/spi.h"
#include "../include/font.h"
#include <stdlib.h>
#include <string.h>

volatile int strobe_state=-1;
volatile long int tic=0;
volatile int msteps=0;
volatile int printingstart=0;
volatile  int step_toggle=0;
volatile uint8_t print_graph=0;
volatile uint8_t print_temp_flag=0;


uint8_t buffer_length=0;
uint8_t global_lines=12;
uint8_t count_lines=0;
char buffer[12][48];
char vertical_buffer[40][2];
uint8_t globalhpos=0;
uint8_t vertical_buffer_length=0;
uint8_t vertical_buffer_pointer=0;
uint8_t count_readings=0;

void setup_strobes()
{
	/*Set up the strobe pins as outputs and pull to LOW*/
	DDR_STROBE |= (STROBE1 | STROBE2 | STROBE3 | STROBE4 |  STROBE5 | STROBE6 );
	PORT_STROBE &= ~(STROBE1 | STROBE2 | STROBE3 | STROBE4 |  STROBE5 | STROBE6 );
}

void paper_out(int num_lines)
{
	PORT_MOTOR &= ~(MDIR_PIN);
	msteps=2*num_lines;
}

void paper_rewind(int num_lines)
{	
	PORT_MOTOR |= (MDIR_PIN);
	msteps=2*num_lines;
}

void stop_sm()
{
	PORT_MOTOR &= ~(MSTEP_PIN);
}

void print_buffer_divided() 
{
 
	if(strobe_state==0)
	{
		start_SPI();
		count_lines=0;
		strobe_state=1;
    }
 
	if(strobe_state==1) 
	{ 
 		if(count_lines<global_lines)
 		{
	 		
	 		
			send_single_line_via_SPI(buffer[count_lines]);
			PORT_SPI &= ~LATCH; //Set Latch pin low to transfer data to the LATCH register
			strobe_state=2; 
		}
		else
		{      
			strobe_state=11;
		}
	
	}
	else if(strobe_state==2) 
	{
		PORT_SPI |= LATCH; //Set Latch pin high again to stop transfer
		PORT_STROBE |= STROBE1;
		strobe_state=3;
	}
	else if(strobe_state==3) 
	{
		PORT_STROBE &= ~STROBE1;  PORT_STROBE |= STROBE2;strobe_state=4;
	}
	else if(strobe_state==4) 
	{
		PORT_STROBE &= ~STROBE2;  PORT_STROBE |= STROBE3; strobe_state=5; 
	}
	else if(strobe_state==5)
	{	 
		PORT_STROBE &= ~STROBE3;  PORT_STROBE |= STROBE4; strobe_state=6;
	}
	else if(strobe_state==6) 
	{
		PORT_STROBE &= ~STROBE4;  PORT_STROBE |= STROBE5; strobe_state=7;
	}
	else if(strobe_state==7)
	{	 
		PORT_STROBE &= ~STROBE5;  PORT_STROBE |= STROBE6; strobe_state=8; 
	}
	else if(strobe_state==8) 
	{
		PORT_STROBE &= ~STROBE6; strobe_state=9; 
	}
	else if(strobe_state==9) 
	{ 
		paper_out(1);
		strobe_state=10;
	}
	else if(strobe_state==10)
	{
		if(!printingstart)
		{
			count_lines++;
			strobe_state=1;     
		}
	}
	else if(strobe_state==11)
	{
		stop_SPI();
		strobe_state=-1;
	}//printing is now complete
}

  

long int map_temp(long int xtemp, long int in_min, long int in_max, long int out_min, long int out_max)
{
	return (xtemp - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
	
}


void data_write_buffer_char(char c)
{	int char_ascii= (int)c;
	int char_index;
	if(char_ascii>=48 && char_ascii<=57)
	{
		char_index=char_ascii-48;
		for(int i=0;i<12;i++)
		{
			buffer[i][globalhpos]=fontint[char_index][i];
		}
	}
	else
	{
		if(char_ascii>=65 && char_ascii<90)  char_index=char_ascii-65;
		else if(char_ascii>=97 && char_ascii<=122) char_index=char_ascii-97;
		else if(char_ascii==32) char_index=26;
		else char_index=27;
		for(int i=0;i<12;i++)
		{
			buffer[i][globalhpos]=font[char_index][i];
		}
		
	}
	
	globalhpos++;
}
void initialize_buffer_lines()
{
	for(int numline=0; numline<12;numline++)
	{
		for(int bytecount=0;bytecount<48;bytecount++)
		{
			buffer[numline][bytecount]=0b00000000;
		}
	}
}

void data_write_buffer_str(char *stringOfCharacters)
{

	initialize_buffer_lines();
	while(*stringOfCharacters>0)
	{
		data_write_buffer_char(*stringOfCharacters++);
	}
	
	
}

void data_write_yaxis()
{
	buffer[0][0]=0b00000000;
	buffer[0][1]=0b00000000;
	for(int bytecount=2;bytecount<48;bytecount++)
	{
		buffer[0][bytecount]=0b11111111;
	}
}

void data_write_buffer_min_max()
{
	//data_write_buffer_str("TEST");
		
		
		initialize_buffer_lines();
		
		char char_range_min[4]="    ";
		char char_range_max[4]="    ";
		itoa(range_min,char_range_min,10);
		itoa(range_max,char_range_max,10);
		globalhpos=2;
		for(int charindex=0;charindex<4;charindex++)
		{
			data_write_buffer_char(char_range_min[charindex]);
		}
		globalhpos=43;
		for(int charindex=0;charindex<4;charindex++)
		{
			data_write_buffer_char(char_range_max[charindex]);
		}		
}


void data_write_buffer_int_vertical(int thenumber)
{			int digits[5];
			int digits_length=-1;
			do
			{	digits_length++;
				digits[digits_length]=thenumber % 10;
				
			} while ((thenumber /= 10) > 0);
			
			do
			{
				int line=vertical_buffer_length;
				int byte_to_read=0;
				int char_index=digits[digits_length];
				
				digits_length--;
				uint8_t line_max=8+vertical_buffer_length;
				for(int line=vertical_buffer_length;line<line_max;line++)
				{
					vertical_buffer[line][0]=fontint_vertical[char_index][byte_to_read];
					byte_to_read++;
					vertical_buffer[line][1]=fontint_vertical[char_index][byte_to_read];
					byte_to_read++;
				}
				
				vertical_buffer_length+=8;
			}while(digits_length>-1);
}


void data_write_temp(uint16_t tempreading)
{

	//data_write_buffer_str("Temperature in deg�");globalhpos=0;
	globalhpos=0;
	
	//tackle problem of combining axis and label
	long int temp_pos=map_temp(tempreading,0,1023,17,383);
	for(int i=0;i<48;i++)
	buffer[0][i]=0b00000000; //set all other bits to 0
	
	if(vertical_buffer_pointer<vertical_buffer_length)
	{
		
		buffer[0][0]=vertical_buffer[vertical_buffer_pointer][0];
		buffer[0][1]=vertical_buffer[vertical_buffer_pointer][1];
		vertical_buffer_pointer++;
	}
	buffer[0][2]=0b10000000; //put the dot for the x axis in the first bit of the third byte
	uint8_t byte_pos=temp_pos/8;
	uint8_t shift_point=(7-temp_pos%8);
	char thisbyte=(1<<shift_point);
	buffer[0][byte_pos]=thisbyte;

}

void test_print(uint16_t tempreading)
{
		if(print_graph==1)
		{
			if(strobe_state==-1)
			{
				count_lines=0;
				count_readings=0;
				global_lines=12;
				globalhpos=2;
				if(print_temp_flag) 
				{
					data_write_buffer_str("Temperature in deg�");
				}
				else 
				{
					data_write_buffer_str("LDR Values");
				}
				strobe_state=0;
				print_graph=3;
			}
		}
		//else if(print_graph==2)
		//{
			//if(strobe_state==-1)
			//{
		//
				//paper_out(4);
				//print_graph=3;
			//}
		//}
		else if(print_graph==3)
		{
			if(strobe_state==-1)
			{
				
				globalhpos=0;global_lines=12;count_lines=0;
				data_write_buffer_min_max();
				strobe_state=0; print_graph=4;
			}
		}
		else if(print_graph==4)
		{
			if(strobe_state==-1)
			{
						
				globalhpos=0;global_lines=1;count_lines=0;
				data_write_yaxis();
				strobe_state=0; print_graph=10;
			}
		}
		else if(print_graph==10)
		{
			if(strobe_state==-1)
			{
				globalhpos=0;global_lines=1;count_lines=0; 
				count_readings++;
				if(count_readings%40==0) 
				{
					vertical_buffer_length=0;
					vertical_buffer_pointer=0;
					data_write_buffer_int_vertical(count_readings);
				}
					
				data_write_temp(tempreading);
				strobe_state=0;
				print_graph=11;
		
			}
		}
		else if(print_graph==11)
		{
			if(strobe_state==-1)
			{
				print_graph=10;
		
			}
		}
		else if(print_graph==20)
		{
			if(strobe_state==-1)
			{
				count_lines=0;
				global_lines=12;
				globalhpos=2;
				data_write_buffer_str("End of Measurement");
				strobe_state=0;
				print_graph=21;
			}
		}
		else if(print_graph==21)
		{
			if(strobe_state==-1)
			{
				paper_out(50);
				print_graph=0;
					
			}
		}

}
/*
void print_temp(uint16_t tempreading)
{
	
			if(print_temp_flag==1)
			{
				if(strobe_state==-1)
				{
					count_lines=0; 
					global_lines=12;
					globalhpos=0;
					data_write_buffer_str("Temperature in deg�");					
					//data_write_buffer_str("LDR Values");globalhpos=16;
					strobe_state=0;
					print_temp_flag=2;
				}
			}
			else if(print_temp_flag==2)
			{
				if(strobe_state==-1)
				{
		
					globalhpos=0;global_lines=1;count_lines=0; 
					data_write_yaxis();
					strobe_state=0; print_temp_flag=3;
				}
			}
			else if(print_temp_flag==3)
			{
				if(strobe_state==-1)
				{
					globalhpos=0;global_lines=1;count_lines=0; 
					data_write_temp(tempreading);
					strobe_state=0;
					print_temp_flag=4;
		
				}
			}
			else if(print_temp_flag==4)
			{
				if(strobe_state==-1)
				{
					print_temp_flag=3;
		
				}
			}
			else if(print_temp_flag==5)
			{
				if(strobe_state==-1)
				{
					count_lines=0;
					global_lines=12;
					//data_write_buffer_str("Temperature in deg�");globalhpos=0;
					globalhpos=16;
					data_write_buffer_str("End of Measurement");
					strobe_state=0;
					print_temp_flag=6;
				}
			}
			else if(print_temp_flag==6)
			{
				if(strobe_state==-1)
				{
					print_temp_flag=0;
					
				}
			}


	  }
	  */
	  void init_printer()
	  {
		  	DDR_MOTOR |= MDIR_PIN | MSTEP_PIN ;
		  	PORT_MOTOR &= ~(MDIR_PIN | MSTEP_PIN );
	 }



