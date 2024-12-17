#include "ADC.h"

void ADCInit(void){
	// turn on the clocking to the ADC module
	SIM->SCGC |= (1u << 29);
	
	// set up the ADC (channel 7)
	
		// enable continous conversion
	ADC->SC1 |= (1u << 5);
	
	// set 12 bit operation
	ADC->SC3 |= (1u << 3);
	
	// enable channel SE7
	ADC->SC1 = 0x7; // 0x16 = temperature reading || 0x7 = channel 7
	
}

void ADCDisable(void){
	
	// disable the adc 
	ADC->SC1 = 0x1F;
	
	// disable the clock to ADC
	SIM->SCGC &= ~(1u << 29);
}

int ADCRead(void){
	
	// wait for a conversion to complete 
	// *** Possible to get stuck here if something goes wrong with ADC *** 
	while((ADC->SC1 & (1u << 7)) != (1u << 7))
		__nop();
	
	return ADC->R;
}
