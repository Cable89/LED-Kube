﻿/*
 * snake.c
 *
 * Created: 20.01.2012 23:59:28
 *  Author: Øystein
 */ 

#include "cube.h"
#include "draw.h"
#include "effect.h"
#include "snake.h"
#include <avr/eeprom.h>

uint16_t EEMEM nonVolatileScore = 0;

int notPlayed = 0;

void snake_game()
{
	snake_x = (unsigned char*) calloc(SNAKE_SIZE,sizeof(unsigned char)); // snake body
	snake_y = (unsigned char*) calloc(SNAKE_SIZE,sizeof(unsigned char));
	snake_z = (unsigned char*) calloc(SNAKE_SIZE,sizeof(unsigned char));
	
	char lost = 0;
	const int speedl[10]={500,450,400,350,300,250,200,180,160,150};
	int	n=0;
	uint16_t score = 0;
	sdir = EAST;
	snake_start_anim();
	initialize_snake();
	place_food();
	draw_snake();
	while (lost==0){
		sdir=sinput;
		if (valid_move()){
			if (isfood()){
				feed_snake();
				place_food();
				score++;
				if (!(score%10)&&(score>0)&&n<9){ // increase speed every 10th food
				n++;
				}
			}
			move_snake();
			clear();
			draw_snake();
			draw_food();
			delay_ms(speedl[n]);
		}
		else
		{lost=1;}
	}
	snake_game_over_anim();
	snake_print_score(score);
	snake_highscore(score);
	
	if (score==0)
	{notPlayed++;}
	else
	{notPlayed=0;}
	if (notPlayed>2)
	{snake_pauseanim();}
		
	free(snake_x);
	free(snake_y);
	free(snake_z);
}



// Place food in the cube, currently only supports one food at a time
void place_food()
{
	food_x = rand()%CUBE_SIZE;
	food_y = rand()%CUBE_SIZE;
	food_z = rand()%CUBE_SIZE;
}

// Necessary to use separate function?
void draw_food()
{
	set_voxel(food_x,food_y,food_z);
}

char isfood()
{
	int x=snake_x[0];
	int y=snake_y[0];
	int z=snake_z[0];
	switch(sdir)  // Use pointers and make this an separate function
	{
		case NORTH: y++; break;
		case WEST:	x--; break;
		case EAST:	x++; break;
		case SOUTH: y--; break;
		case UP:	z++; break;
		case DOWN:	z--; break;
		default: return 0;
	}
	if(x==food_x && y==food_y && z==food_z)
	{return 1;}
	else
	{return 0;}
}

void initialize_snake ()
{
	int x = 5;
	int y = 4;
	int z = 4;
	sinput = EAST;
	for (int i=0;i<SNAKE_START;i++) // The snake body is filled with valid coordinates
	{
		snake_x[i] = x;
		snake_y[i] = y;
		snake_z[i] = z;
		x--;
	}
	for (int i=SNAKE_START;i<SNAKE_SIZE;i++) // The inactive part of the snake body is filled with invalid coordinates
	{
		snake_x[i] = 0xff;
		snake_y[i] = 0xff;
		snake_z[i] = 0xff;
	}
}

// This function checks whether the snake is allowed to move in the desired direction
// Char input N,W,E,S,U,D (North,West,East,South,Up,Down)
unsigned char valid_move()
{
	int x=snake_x[0];
	int y=snake_y[0];
	int z=snake_z[0];
	
	switch(sdir)
	{
		case NORTH: y++; break;
		case WEST:	x--; break;
		case EAST:	x++; break;
		case SOUTH: y--; break;
		case UP:	z++; break;
		case DOWN:	z--; break;
		default: return 0;
	}
	
	if (inrange(x,y,z) && (!getvoxel(x,y,z) || isfood()))
		{return 1;}
	else
		{return 0;}
}


// This function moves the snake
void move_snake()
{
	int i=0;
	int x,y,z;
	int next_x=snake_x[0];
	int next_y=snake_y[0];
	int next_z=snake_z[0];
	//next_coordinates(next_x,next_y,next_z,dir);
	
	switch(sdir)
	{
		case NORTH: next_y++; break;
		case WEST:	next_x--; break;
		case EAST:	next_x++; break;
		case SOUTH: next_y--; break;
		case UP:	next_z++; break;
		case DOWN:	next_z--; break;
		default:	break;
	}
	
	while (inrange(next_x,next_y,next_z)&&(i<SNAKE_SIZE)) // While working with the active part of the snake body
	{
		x=snake_x[i];
		y=snake_y[i];
		z=snake_z[i];
		if (inrange(x,y,z))
		{
			snake_x[i]=next_x;
			snake_y[i]=next_y;
			snake_z[i]=next_z;
		}
		next_x=x;
		next_y=y;
		next_z=z;
		i++;
	}	
}

// Feeds the snake (increases length)
void feed_snake()
{
	int i=0;
	while(inrange(snake_x[i],snake_y[i],snake_z[i]))
	{i++;}
	snake_x[i]=snake_x[i-1];
	snake_y[i]=snake_y[i-1];
	snake_z[i]=snake_z[i-1];
}

// Draws the snake in the cube
void draw_snake()
{
	int i=0;
	while ((i<SNAKE_SIZE)&&inrange(snake_x[i],snake_y[i],snake_z[i]))
	{
		set_voxel(snake_x[i],snake_y[i],snake_z[i]);
		i++;
	}
}

// Reads from the controller
// Char output N,W,E,S,U,D (North,West,East,South,Up,Down)
void snake_input()
{
	if      ((PIND==0xfb) && !(sdir==SOUTH))
	{sinput = NORTH;} 
	else if ((PIND==0xf7) && !(sdir==NORTH))
	{sinput = SOUTH;}
	else if ((PIND==0xef) && !(sdir==WEST))
	{sinput = EAST;}
	else if ((PIND==0xdf) && !(sdir==EAST))
	{sinput = WEST;}
	else if ((PIND==0xbf) && !(sdir==DOWN))
	{sinput = UP;}
	else if ((PIND==0x7f) && !(sdir==UP))
	{sinput = DOWN;}		
}

// Startup animation for the snake game
void snake_start_anim()
{
	clear(); // Just in case
	effect_path_text(80,"SNAKE");
	clear();
	effect_stringfly2("3D");
	clear();
}

// Game over animation for the snake game
void snake_game_over_anim()
{
	clear();
	for (int i=0;i<10;i++)
	{
		draw_snake();
		delay_ms(100);
		clear();
		delay_ms(100);
	}
}

// Animation that runs when no one is playing
void snake_pauseanim()
{
	while (sinput==EAST)
	{
		effect_rain(2,80);
	}
}

// Prints the score
void snake_print_score(uint16_t score)
{
	char buf[5];
	itoa(score,buf,10);
	effect_stringfly2(buf);
}

// Stores one high score in EEPROM (expand to larger list with nick input)
char snake_highscore(uint16_t score)
{
	if (score>eeprom_read_word(&nonVolatileScore))
	{
		eeprom_write_word(&nonVolatileScore,score);
		effect_path_text(80,"NEW HIGHSCORE");
		return 1;
	}
	else
	{
		return 0;
	}
}

void snake_menu(){
	while (!(nesControllerData == NES_START)){
		if (nesControllerData == NES_A){
			effect_path_text(80,"HIGHSCORE");
			snake_print_score(eeprom_read_word(&nonVolatileScore));
		}
	}
}