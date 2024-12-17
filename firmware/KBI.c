#include "KBIDriver.h"


// initialize KBI
void KBIInit(void){
		// ---- KBI ---- 
	// Button is on KBI0_P7 / PTB3 // GPIO 11 
	// falling edge
	// interrupt
	
	// enable clock gate for KNI0
	SIM->SCGC |= (1u << 24);
	
	// set pin as input
	GPIOA->PIDR &= ~(1u << 11);
	
	// enable pin 7 as KBI 
	KBI0->PE |= (1u << 7);
	
	// enable the interrupt
	KBI0->SC |= (1u << 1);
	
	// enable ARM interrupts for KBI0
	NVIC_EnableIRQ(KBI0_IRQn);
	
}
