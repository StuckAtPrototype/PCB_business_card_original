#ifndef GAMEFUNCTIONS_H
#define GAMEFUNCTIONS_H

#include "MKE04Z4.h" 
#include "typedef.h" // custom bool and etc. 
#include "PIT.h" // timers
#include "Enemy.h" // enemy "class"

// game started var
extern bool game_started; 

// start gameplay
// clears all variables, resets the game, introduces 
// new seed for rand() and starts timers
void GameStart(void);


// stop gameplay
// displays the score
// resets the screen
// stops timers
void GameStop(void);

#endif
