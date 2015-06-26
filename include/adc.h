/*
 * adc.h
 *
 * Created: 30.05.2015 20:08:20
 *  Author: TwoBit
 */ 

#ifndef ADC_H_
#define ADC_H_

#include "globals.h"

void adc_init(void);            						// Init ADC
void adc_stop(void);            						// Stops ADC
uint16_t adc_get(uint8_t channel);						// Read ADC Value

#endif /* ADC_H_ */