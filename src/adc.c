/*
 * adc.c
 *
 * Created: 30.05.2015 20:07:46
 *  Author: TwoBit
 */ 

#include "../include/adc.h"

void adc_init(void){
							//ADPS = 7(Vorteiler 128)
	ADCSRA |= (1<<ADPS2)			// 0 | 0 | 1 -> Prescaler = 2;
		   |  (1<<ADPS1)			// 0 | 1 | 0 -> Prescaler = 4;
		   |  (1<<ADPS0)			// 0 | 1 | 1 -> Prescaler = 8;
									// 1 | 0 | 0 -> Prescaler = 16;
									// 1 | 0 | 1 -> Prescaler = 32;
									// 1 | 1 | 0 -> Prescaler = 64;
									// 1 | 1 | 1 -> Prescaler = 128;
		   |  (1<<ADEN);			// ADC Enable
		   							
	ADMUX |= (1<<REFS1)
		  |  (1<<REFS0);			// Internal 2.56V Voltage Reference with external capacitor at AREF pin

	// Dummy conversion
	ADCSRA |= (1<<ADSC);
	while ( ADCSRA & (1<<ADSC) ); 	// Wait till ready

}            						
void adc_stop(void){
	ADCSRA &= ~(1<<ADEN);
}    	
uint16_t adc_get(uint8_t channel){
	ADMUX = (ADMUX & 0b1110000) | channel;	// Choose channel

	ADCSRA |= (1<<ADSC);        			// Single Conversion
	while(ADCSRA & (1<<ADSC));
	return ADC;
}						