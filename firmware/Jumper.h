#ifndef JUMPER_H
#define JUMPER_H

#include "MKE04Z4.h" 
#include "typedef.h" // custom bool and etc. 
#include "GameFunctions.h" 

// position of the jumper					
extern uint16_t jumper_pos;

// jumper function exposed for testing
void 	JumperSetEnergy(uint16_t);
	

#endif
