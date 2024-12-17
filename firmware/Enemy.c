#include "Enemy.h"

// enemy screen in pixels. 0 = off, 1 = on
uint16_t current_enemy_screen[3][7] = {
																				{0, 0, 0, 0, 0, 0, 0},
																				{0, 0, 0, 0, 0, 0, 0},
																				{0, 0, 0, 0, 0, 0, 0}
																			};
	
// enemy figures 
uint16_t enemy_3d[7][3][2] = {

	{
		{0,0},
		{0,0},
		{1,0}
	},
	{
		{0,0},
		{1,0},
		{1,0}
	},
	{
		{0,0},
		{1,0},
		{1,0}
	},
		{
		{0,0},
		{1,1},
		{0,0}
	},
	{
		{0,0},
		{1,0},
		{0,0}
	},
	{
		{1,0},
		{1,0},
		{0,0}
	},
		{
		{0,0},
		{0,0},
		{1,0}
	}
};

// delay for the next enemy generation
uint16_t delay = 3; 
uint16_t delay_tick = 0;

// speed of the game 
const uint32_t game_speed_const = 4500000; // 4500000
uint32_t game_speed = 4500000; 
const uint32_t game_speed_min = 2750000; // 2750000 = 114ms || 3500000 = 146ms
const uint32_t game_speed_step = 5000;

// light up a specific LED
void EnemyControlLEDDirect(uint16_t row, uint16_t col, uint16_t value){
	
	// if 1 turn on, if 0 turn off
	if(value == 1)
		GPIOA->PCOR = (1u << enemy_screen_definition[row][col]);
	else
		GPIOA->PSOR = (1u << enemy_screen_definition[row][col]);
}

// clear the enemy screen
// does not turn off leds unless EnemyAnimate is ran! 
void EnemyClearScreen(void){
		// clear current enemy screen
	for(int i = 0; i < 3; i++){
		for(int b = 0;b < 7; b++){
			current_enemy_screen[i][b] = 0;
		}
	}
}

// initialize or re-initialize 
void EnemyInit(uint32_t seed){
	
	// pass in the seed
	srand(seed);
	
	// clear enemy screen
	EnemyClearScreen();
	
	// game_speed reset
	game_speed = game_speed_const;
	
	// reset the delay tick
	delay_tick = 0;
}


void EnemyScreenRedraw(void){
		// turn on/off leds 
	for(int i = 0; i < 3; i++){
		for(int b = 0; b < 5; b++){
			// turn off the led if 0 turn on if 1
			if(current_enemy_screen[i][b] == 0)
				GPIOA->PSOR = (1u << enemy_screen_definition[i][b]);
			else 
				GPIOA->PCOR = (1u << enemy_screen_definition[i][b]);
		}
	}
}


// animates and renders the pixels
void EnemyAnimate(){

	// translate the enemy screen left by 1 column
	for(int i = 0; i < 6; i++){
		// translate entire colum
		for(int b = 0; b < 3; b++)
			current_enemy_screen[b][i] = current_enemy_screen[b][i+1];
	}		
	// clear the last 3 
	for(int i = 0; i < 3; i++)
		current_enemy_screen[i][6] = 0;
	
	// redraw the screen
	EnemyScreenRedraw();
	
}	


void GenerateEnemy(){
	
	// generate a random number
	int num = rand(); // 0 to 0x7FFFFFFF
	num /= 306783378; 
	
	// just in case
	if(num >= 7)
		num = 6;
	
	// set up an enemy
	for(int i = 0; i < 3; i++){
		for(int b = 0; b < 2; b++){
			current_enemy_screen[i][b + 5] = enemy_3d[num][i][b];
		}
	}
	
}

// adjust the enemy speed as game progresses
void EnemySpeedAdjust(void){
	
	// adjust the game speed at different rates through out
	if(game_speed > (game_speed_min + 300000)){
		game_speed -= game_speed_step;
	}
	else if(game_speed > game_speed_min){
		game_speed -= game_speed_step/5;
	}
	
}

// PIT 1 (PWM) interrupt
// main loop for enemy
// takes care of animating enemy
// and checking if jumper has been hit
void PIT_CH1_IRQHandler(void){
	
	// animate the screen
	EnemyAnimate();

	
/* uncomment if you want the jumper to be automated
	if(current_enemy_screen[2][3] == 1)
		// run the jumper! 
		JumperSetEnergy(4);
	else if(current_enemy_screen[2][2] == 1)
		// run the jumper! 
		JumperSetEnergy(4);
*/
	
	
	// check if jumper hit an enemy
	for(int i = 0; i < 3; i++){
		
		// check if the enemy screen is a 1
		if(current_enemy_screen[i][0] == 1){
			if(jumper_pos == 2 - i){
				// jumper hit! 	
				// end the game
				GameStop();
				
				// reset the frequency of the PIT timer -- might not need this
				PIT->CHANNEL[1].LDVAL = game_speed_const;
				
				PIT->CHANNEL[1].TFLG = 0x1; // clear the irq
				NVIC_ClearPendingIRQ(PIT_CH1_IRQn); // clear ARM irq
				
				return;
			}
		
		}
			
	}
	
	// generate a new enemy if delay allows
	if( delay_tick >= delay){
		GenerateEnemy();
		delay_tick = 0;
		
		// establish the next delay 3 to 8
		int num = rand(); // 0 to 0x7fffff
		num /= 429496729; 
		num += 3;
		
		if(num >= 9)
			num = 8;
		
		delay = num;
	}
	else
		delay_tick++;

	// make the game faster
	EnemySpeedAdjust();

	
		// reset the frequency of the PIT timer with new game speed
	PIT->CHANNEL[1].LDVAL = game_speed;
	
	PIT->CHANNEL[1].TFLG = 0x1; // clear the irq
	NVIC_ClearPendingIRQ(PIT_CH1_IRQn); // clear ARM irq
	
}


