#include "LEDS.h"

// assign values 
int leds_score[15] = {LED18, LED17, LED16, LED15, LED14, LED13,
											LED12, LED11, LED10, LED9, LED8, LED7, 
											LED3, LED2, LED1};

int leds[18] = {LED1, LED2, LED3, LED4, LED5, LED6, 
									LED7, LED8, LED9, LED10, LED11, LED12, 
										LED13, LED14, LED15, LED16, LED17, LED18}; 
uint16_t enemy_screen_definition[3][5] = {
																						{LED1, LED7, LED10, LED13, LED16},
																						{LED2, LED8, LED11, LED14, LED17},
																						{LED3, LED9, LED12, LED15, LED18}
																					};	
uint16_t jumper_screen_definition[3] = {LED6,LED5,LED4};
