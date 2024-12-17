#ifndef ADC_H
#define ADC_H

#include "MKE04Z4.h" 
#include "typedef.h" // custom bool and etc. 

// initialize the adc unit to read form channel 7
void ADCInit(void);

// turn off the ADC for power saving
void ADCDisable(void);

// read the ADC 
int ADCRead(void);

#endif
