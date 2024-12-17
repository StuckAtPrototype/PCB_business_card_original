#ifndef PIT_TIMER
#define PIT_TIMER

#include "MKE04Z4.h" 
#include "typedef.h" // custom bool and etc. 

// Limited PIT timer driver

// initializes the PIT timers
void PIT_Init(void);
void PIT_StartTimers(void);
void PIT_StopTimers(void);

#endif
