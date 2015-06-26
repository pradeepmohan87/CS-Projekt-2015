/*
 * timer.h
 *
 * Created: 30.05.2015 16:05:50
 *  Author: TwoBit
 */ 
#ifndef TIMER_H_
#define TIMER_H_

#include <avr/interrupt.h>
#include "globals.h"

#define STROBEDELAY 4

extern volatile int strobe_state;
extern volatile long int tic;
extern volatile int printingstart;
extern volatile int msteps;
extern volatile int step_toggle;


void timer0_init(void);
void timer1_init(void);
extern void int1Hz(void);
extern void int10Hz(void);
extern void int100Hz(void);
extern void int1kHz(void);
extern void int10kHz(void);

#endif /* TIMER_H_ */