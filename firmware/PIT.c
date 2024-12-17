#include "PIT.h"


// initialize the PIT peripheral
void PIT_Init(){
	
	SIM->SCGC |= (1u << 1); // enable PIT clock (bus source)
	
	PIT->MCR &= ~(1u << 1); // clear the bit to enable PIT timer
	
	// PIT channel 0
	PIT->CHANNEL[0].LDVAL = 3000000; // set the count down to 0, off 
	

	PIT->CHANNEL[0].TCTRL |= (1u << 1); // enable irq
	
	PIT->CHANNEL[0].TFLG = 0x1; // clear the irq 
	
	// make sure that timer 1 is diabled
	PIT->CHANNEL[0].TCTRL &= ~(1u << 0); 
	
	// enable ARM irq
	NVIC_EnableIRQ(PIT_CH0_IRQn);
	
	// start timer 1 
	PIT->CHANNEL[0].TCTRL &= ~(1u << 0); // disable the timer
	// PIT->CHANNEL[0].TCTRL |= (1u << 0); // enable the timer
	
	// PIT channel 1
	PIT->CHANNEL[1].LDVAL = 4000000; // set the count down to 0, off 
	

	PIT->CHANNEL[1].TCTRL |= (1u << 1); // enable irq
	
	PIT->CHANNEL[1].TFLG = 0x1; // clear the irq 
	
	// make sure that timer 1 is diabled
	PIT->CHANNEL[1].TCTRL &= ~(1u << 0); 
	
	 
	// enable ARM irq
	NVIC_EnableIRQ(PIT_CH1_IRQn);
	
	// start timer 1 
	PIT->CHANNEL[1].TCTRL &= ~(1u << 0); // disable the timer
	// PIT->CHANNEL[1].TCTRL |= (1u << 0); // enable the timer
}


// start timers 0 and 1
void PIT_StartTimers(){
	PIT->CHANNEL[0].TCTRL |= (1u << 0); // enable the timer
	PIT->CHANNEL[1].TCTRL |= (1u << 0); // enable the timer
}

// stop timers 0 and 1
void PIT_StopTimers(){
	PIT->CHANNEL[0].TCTRL &= ~(1u << 0); // disable the timer
	PIT->CHANNEL[1].TCTRL &= ~(1u << 0); // disable the timer
}
