// REGISTERS.C

#include "Registers.h"

uint8_t direction_keeper = 0;

uint32_t last_speed = 0;

// changes the speed for the motors
void REGISTERS_ChangeSpeed(uint8_t speed, uint8_t direction){
	
	// speed byte 
	if(speed == 0x10 || speed == 0x00 || speed == 0x1 || speed == 0x11)
	{
		// STOP
		// set both of the lines (high only for now - i.e break)
		//PTA->PSOR = (1 << 18); // MOTOR ON
		//PTA->PSOR = (1 << 19); // MOTOR ON
		GPIOA->PCOR = (1u << 18); // MOTOR OFF 
		GPIOA->PCOR = (1u << 19); // MOTOR OFF 
		
		// PWM MOTOR LINE 0
		PIT_SetPWMLine(0);
		PIT_SetTimer1DutyCycle(2400);
		__nop();
		
	}
	else{
		
		// filter bit 5 (mid step) for now by using only bits 0 to 3
		//speed &= 0b1111;
		
		// this gives us only 14 steps of resolution (approximately 170 per step)
		// max speed = 0 freq, and min speed = 2400 freq 
		uint32_t speed_freq = 2400;
		
		// speed can be in the range of 2 to 15, thus we need to add 1 to 14, making it 15
		speed_freq = (speed - 1) * 170;

		PIT_SetTimer1DutyCycle(speed_freq);
		
		
		// update the speed and direction
		if(direction == 0x0){ // SPEED_FORWARD
			// FORWARD
			
			GPIOA->PCOR = (1u << 18); // MOTOR OFF 
			
			// PWM MOTOR LINE 19
			PIT_SetPWMLine(19);


		}
		else if(direction == 0x1)
		{
			// REVERSE

			GPIOA->PCOR = (1u << 19); // MOTOR OFF 
			
			// PWM MOTOR LINE 18
			PIT_SetPWMLine(18);

			
			
		}
		
	}
	
}

void REGISTERS_ChangeFunctionGroupOne(uint8_t functions){
	// functions format xxxDDDDD
	// *** TODO implement CV#29 check for bit 1 ***
	
	// toggle FL
	if((functions & FUNCTIION_FL_MASK) == FUNCTIION_FL_MASK)
	{
		// turn on the headlights (all for now)
		GPIOA->PSOR = (1 << 13); // LED ON
		GPIOA->PSOR = (1 << 17); // LED ON
				
	}
	else
	{
		// turn off the headlights (all for now)
		GPIOA->PCOR = (1u << 13); // LED OFF 
		GPIOA->PCOR = (1u << 17); // LED OFF 
	}
	
}
