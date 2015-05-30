/*
 * timer.h
 *
 * Created: 30.05.2015 16:05:50
 *  Author: TwoBit
 */ 


#ifndef TIMER_H_
#define TIMER_H_

#include <avr/io.h>
#include <avr/interrupt.h>

void timer_init(void);
extern void int1Hz(void);
extern void int10Hz(void);
extern void int100Hz(void);
extern void int1kHz(void);
extern void int10kHz(void);

#endif /* TIMER_H_ */