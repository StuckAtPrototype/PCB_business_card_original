#ifndef LEDS_H
#define LEDS_H

#include "MKE04Z4.h" 
#include "typedef.h" // custom bool and etc. 

// LED mapping
#define LED1 8  // PTB0
#define LED2 9  // PTB1
#define LED3 10 // PTB2
#define LED4 16 // PTC0
#define LED5 17 // PTC1
#define LED6 18 // PTC2
#define LED7 19 // PTC3
#define LED8 12 // PTB4
#define LED9 13 // PTB5
#define LED10 14 // PTB6
#define LED11 15 // PTB7 
#define LED12 20 // PTC4
#define LED13 21 // PTC5
#define LED14 1 // PTA1
#define LED15 2 // PTA2
#define LED16 3 // PTA3
#define LED17 6 // PTA7
#define LED18 7 // PTA6


extern int leds_score[15]; 
extern int leds [18]; 
extern uint16_t enemy_screen_definition[3][5];	
extern uint16_t jumper_screen_definition[3];

#endif
