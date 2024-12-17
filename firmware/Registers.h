#include <stdint.h>
#include "typedef.h"
#include "MKE04Z4.h" // all chip related crap
#include "PIT.h"

#ifndef REGISTERSH
#define REGISTERSH

// public vars
// function group one masks
#define FUNCTIION_FL_MASK 0x10


// public functions

// changes the speed for the motors
void REGISTERS_ChangeSpeed(uint8_t, uint8_t);

// changes the function vars
void REGISTERS_ChangeFunctionGroupOne(uint8_t);

#endif
