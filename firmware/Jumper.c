#include "Jumper.h"
#include "LEDS.h"

// vars
uint16_t jumper_pos = 0;
uint16_t jumper_energy = 0;

// sets the jumpers energy
void JumperSetEnergy(uint16_t energy){
	// set the energy only if it at 0
	if(jumper_energy == 0)
		jumper_energy = energy;
}
	

// PIT 0 interrupt - jumper animation
void PIT_CH0_IRQHandler(void){
	

	
	// animate the jumper
	if(jumper_energy > 0){
		jumper_energy--;
		jumper_pos++;
		if(jumper_pos > 2)
			jumper_pos = 2;
	}
	else{
		
		if(jumper_pos > 0)
			jumper_pos--;
	}
	
	// turn off all positions
	for(int i = 0; i < 3; i++)
		GPIOA->PSOR = (1u << jumper_screen_definition[i]);
	
	// turn on jumper at the approperiate position
	GPIOA->PCOR = (1u << jumper_screen_definition[jumper_pos]);
	
	
		// reset the frequency of the PIT timer -- might not need this
	PIT->CHANNEL[0].LDVAL = 3000000;
	
	PIT->CHANNEL[0].TFLG = 0x1; // clear the irq
	NVIC_ClearPendingIRQ(PIT_CH0_IRQn); // clear ARM irq
	
}
