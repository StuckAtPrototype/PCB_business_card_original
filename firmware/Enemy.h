#ifndef ENEMY_H
#define ENEMY_H

#include "MKE04Z4.h" 
#include "typedef.h" // custom bool and etc. 
#include "LEDS.h"
#include "Jumper.h"
#include "GameFunctions.h"
#include <stdlib.h>

// initialization/reinitialization
// reinitializes the seed for rand()
void EnemyInit(uint32_t);

// forces a screen refresh based on current_enemy_screen definition
// this function is ran automatically by timers in game mode
// current_enemy_screen needs to be modified before running 
void EnemyScreenRedraw(void);

// direct control over specific LEDs
void EnemyControlLEDDirect(uint16_t row, uint16_t col, uint16_t value);

#endif
