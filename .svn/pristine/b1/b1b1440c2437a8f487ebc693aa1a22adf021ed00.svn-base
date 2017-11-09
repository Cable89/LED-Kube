/*
 * snake.h
 *
 * Created: 21.01.2012 13:45:38
 *  Author: Øystein
 */

#ifndef SNAKE_H_
#define SNAKE_H_


#define NORTH 0x4e // Ascii N
#define SOUTH 0x53 // Ascii S
#define EAST  0x45 // Ascii E
#define WEST  0x57 // Ascii W
#define UP	  0x55 // Ascii U
#define DOWN  0x44 // Ascii D
#define SNAKE_SIZE 200
#define SNAKE_START 3




int food_x; // Use pointers instead?
int food_y;
int food_z;

char sdir;   // Actual direction of snake
char sinput; // Input from controller to snake

unsigned char snake_x[SNAKE_SIZE]; // snake body (make smaller, even possible to run on the atmega?)
unsigned char snake_y[SNAKE_SIZE]; // Pointer?
unsigned char snake_z[SNAKE_SIZE];


void snake_game();
void place_food();
void draw_food();
char isfood();
void initialize_snake ();
unsigned char valid_move();
void move_snake();
void feed_snake();
void draw_snake();
void snake_input();
void snake_start_anim();
void snake_game_over_anim();
void snake_pauseanim();
void snake_print_score(uint16_t score);
char snake_highscore(uint16_t score);


#endif /* SNAKE_H_ */

 



/* Ideer til snake:

Animasjon hvis ingen spiller (Delvis løst, må skrive en "snake animasjon")
Flerspiller
Highscoreliste
Snake logo

2012-01-29 Input fra OC:
Separate variabler for input fra kontroller og faktisk retning på slangen
Easy/Hardcore mode


Changelog

2012-01-20
Programmeringsstart
2012-01-21
Programmering
2012-01-22
Testing og input av ideer

2012-01-29
Lagt til oppstartsvalg: spille snake eller vise effekter
Lagt til enkel lagring av 1 highscore
*/