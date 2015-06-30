/*
 * timer.c
 *
 * Created: 30.05.2015 16:05:33
 *  Author: TwoBit
 */ 
#include "../include/timer.h"
#include "../include/printer.h"

volatile uint16_t cnt_sema;					// volatile: counting semaphore

ISR(TIMER0_COMP_vect){
	//cnt_sema++;
								 int10kHz();	//  10 kHz Interrupt
	//if((cnt_sema % 10)    ==  0) int1kHz();	//   1 kHz Interrupt => 1ms wait 10 times 
	//if((cnt_sema % 100)   ==  0) int100Hz();	// 100  Hz Interrupt => 10ms wait 100 times
	//if((cnt_sema % 1000)  ==  0) int10Hz();	//  10  Hz Interrupt => 100ms wait 1000 times
	//if((cnt_sema % 10000) ==  0){				//   1  Hz Interrupt => wait 10.000 times
		 //int1Hz();								
		 //cnt_sema = 0;						//   reset Interrupts Counter
	//}
}

 void timer0_init(void){
	cnt_sema = 0;					//Start Value for the Interrupt Counter

	 // f=1MHz/(100)  =  10kHz => 0,100 ms	 
	 TCCR0 |= (0 << COM00)
		   |  (0 << COM01);			// Normal Port Operation OC0 disconneted
	 
									// 02| 01| 00
	 TCCR0 |= (0<<CS02)				// 0 | 1 | 0 -> Prescaler = 8;
		   |  (0<<CS01)				// 0 | 1 | 1 -> Prescaler = 64;
		   |  (1<<CS00);			// 1 | 0 | 0 -> Prescaler = 256;
									// 1 | 0 | 1 -> Prescaler = 1024;
							
	 TCCR0 |=  (1<<WGM01)			// Enable CTC Mode
		   |   (0<<WGM00);
	 TIFR  |=  (1<<OCF0);			// Clearing Flag 
	 TIMSK |=  (1<<OCIE0);			// Enable CTC Interrupts
	 	 
	 TCNT0 	=  0x00;				// Start Value for Timer/Counter Reg
	 OCR0   =  100-1;				// Compare Value (starting from 0 so -1)
 }
 
 ISR(TIMER1_COMPA_vect)
 { 
	tic=tic+1;
	if(tic%STROBEDELAY==0)
	{
		if(strobe_state>-1) { print_buffer_divided(); }
	}
	if(tic % sample_rate==0)//should be actually based on sampling rate set by user..
	{
		if(print_graph)
		{
			temp++;
			if(print_temp_flag) test_print(temp);
			else test_print(ldr_value);
		}
	}
	 
	if(msteps>0){
		if(!printingstart) printingstart=1;
		//step_toggle=!step_toggle;
		if(step_toggle) step_toggle=0;
		else step_toggle=1;
		 
		PORT_MOTOR ^= (MSTEP_PIN);

		if(!step_toggle) { msteps--; }
	}
	else{ 
	if(printingstart)
		printingstart=0;
	}
 }
 
 
 void timer1_init()
 {
	 TCCR1A=0b00000000;
	 TCCR1B=0b00000000;

	 TCCR1B |= ((1<<WGM12) | (1<< CS10));
	 TCNT1=0;
	 OCR1A=1999;//2ms  prescaler 1
	 TCNT1=0;
	 TIMSK |= (1<<OCIE1A);
 }