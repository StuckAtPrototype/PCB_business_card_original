#include <stdint.h>
#include <stdlib.h>
#include "MKE04Z4.h" // all chip related crap
#include "typedef.h" // custom bool and etc. 
#include "PIT.h" // PIT driver
#include "LEDS.h" // leds mapping
#include "KBIDriver.h" // KBI driver
#include "GameFunctions.h"
#include "ADC.h" // ADC driver
															
int main (void){
	
		// --- SYSTICK ---
	SysTick_Config(SystemCoreClock /6);
	
	
	// pin 13 is pulled up to batt by 10k resistor
	// this should vary in voltage as battery ages, 
	// as battery is drained and as load varies
	// pin 13 default is ADC0_SE7 - use is as random (init) seed
	// initialize the adc 
	ADCInit();
	
	// read the result from ADC_R	
	// use the result as a random seed for rand() 
	srand(ADCRead());
	
	// disable the adc for power saving
	ADCDisable();
	
	// set up the GPIO 
	for(int i = 0; i < 18; i++){
		// set all leds as output	
		GPIOA->PDDR |= (1u << leds[i]);
		// turn off all leds
		GPIOA->PSOR |= (1u << leds[i]);
		
	}
	
	// disable the NMI 
	SIM->SOPT &= ~(1u << 1);
	
	// initialize the KBI module
	KBIInit();
		
	// initialize PIT 
	PIT_Init();
	

	// rest of the program is executed based on interrupts
	// either from button press or timers
	// never quit 	
	while(1)
		__nop();
	
}
