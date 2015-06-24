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

void timer_init(void);
extern void int1Hz(void);
extern void int10Hz(void);
extern void int100Hz(void);
extern void int1kHz(void);
extern void int10kHz(void);

#endif /* TIMER_H_ */