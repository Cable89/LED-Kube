/*
 * Led Cube 10x10x10 Red
 * cube.h
 *
 * Created: 08.10.2011 19:35:57
 *  Author: Øystein
 */ 


#ifndef CUBE_H_
#define CUBE_H_

// Set the size of the cube here
#define CUBE_SIZE 10

// CPU speed for delay function
# define F_CPU 16000000

volatile unsigned int cube[CUBE_SIZE][CUBE_SIZE]; // Cube buffer

#define AXIS_X 0x78 // x
#define AXIS_Y 0x79 // y
#define AXIS_Z 0x7a // z

#endif /* CUBE_H_ */


/*
Things to add on the controller board

Power Supply
LCD for high scores etc
Buttons next to LCD
USB Host
NES-Controller input
USB Client for input from PC
Speaker
Status LEDs
Audio in (for VU-meter)
microphone

*/

/*
Possible games

Tetris
Space invaders
Light cycles (Achtung)


*/