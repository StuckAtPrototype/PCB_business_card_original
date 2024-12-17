#include "GameFunctions.h"

// game started bool
bool game_started = false;

// show score bool
bool game_show_score = false;

// score position for score display loop
uint16_t game_score_pos = 0;

// animate score init bool
bool game_init_animate_score = false;

// seed for the rand()
int seed = 0;

// program state
uint16_t game_program_state = 0; 

// game score
uint32_t game_score = 0;

// ++ game score 
void GameUpScore(void){
	
	game_score ++; 
	
}

// calculate the game score
void GameCalculateScore(void){
	
	// normalize the game score -- we have 15 available leds			
	game_score /= 30;
	
 	if(game_score > 14)
		game_score = 14;
	
}

void GameIntroRandomSequence(void){
		
	// generate a random number 
	int random = rand();
	
	// normalize the random number
	random /= 143165576; // 0 to 17
	
	// make sure its not above 17 and not below 0
	if(random > 14)
		random = 14;
	else if(random < 0)
		random = 0;
	
	// toggle a led! 
	GPIOA->PTOR = (1u << leds_score[random]);
	
}



// display the score on the enemy screen
void GameAnimateScore(void){
	
	// check if the animation of the score has started
	if(game_init_animate_score == false){
		// clear the jumper and enemy screen
		for(int i = 0; i < 18; i++){
			GPIOA->PSOR = (1u << leds[i]);
		}
		game_init_animate_score = true;
	}
	
	// check if we should still do this
	if(game_score_pos <= game_score){
		
		// light up the specific position
		GPIOA->PCOR = (1u << leds_score[game_score_pos]);
		
		// up the score pos
		game_score_pos++;
	}
	
}


// start the game
void GameStart(void){
	
	// declare game started 
	game_started = true;
	
	// clear all variables except the seed
	EnemyInit(seed);
	game_score = 0;
	game_score_pos = 0;
	game_init_animate_score = false;
	
	// start timers
	PIT_StartTimers();
		
}

void GameStop(void){
	
	// declare game stopped
	game_started = false;
	
 	// stop timers
	PIT_StopTimers();
	
	// normalize the score of the game
	GameCalculateScore(); 
}


// pre-game/post-game loop 
void SysTick_Handler(void)  {   

	// up our seed to make it as random as possible
	seed++;

	// determine the state of the program and follow through
	switch(game_program_state){
		
		case 0:
			// intro 
			GameIntroRandomSequence();
			break;
		case 1:
			// gameplay
			break;
		case 2:
			// flash
			game_show_score = true;
			break;

		default:
			break;
		
	}
	
	// up the game score if the game is started
	if(game_started == true)
		game_score ++; 

	if(game_show_score == true){
		GameAnimateScore();
		game_show_score = false;
	}
		
}

// KBI interrupt on falling edge. button press 
// PIT 0 interrupt - jumper animation
void KBI0_IRQHandler(void){ 
    
    // if game is not started, start the game and exit
    if(!game_started){
			// up the game_program_state 
			game_program_state++;

			// check to make sure we are not overflowing
			if(game_program_state > 2)
				game_program_state = 1;
			
			// start the game if we are in state of 1
			if(game_program_state == 1){
				GameStart();
				// kick start the jumper for the effect
				JumperSetEnergy(4);
			}
				
			// debounce delay
			for(int i = 0; i < 1000000; i++)
				__nop();
			
			
			// clear the KBI interrupt flag
			KBI0->SC |= (1u << 2);
			
			// clear ARM IRQ
			NVIC_ClearPendingIRQ(KBI0_IRQn);
			
			// end the function here
			return;
    }
    
    // run the jumper! 
    JumperSetEnergy(4);
    
    // clear the KBI interrupt flag
    KBI0->SC |= (1u << 2);
    
    // clear ARM IRQ
    NVIC_ClearPendingIRQ(KBI0_IRQn);
        
}
