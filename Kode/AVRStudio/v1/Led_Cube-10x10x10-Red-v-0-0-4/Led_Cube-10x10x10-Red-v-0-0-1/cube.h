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
#define F_CPU 16000000

// Set baud rate for USB
// Define USART stuff
#define FOSC 16000000
#define BAUD 57600
#define MYUBRR (((((FOSC * 10) / (16L * BAUD)) + 5) / 10) - 1)

volatile unsigned int cube[CUBE_SIZE][CUBE_SIZE]; // Cube buffer [z][y]

char nesControllerData;

#define NES_STROBE_MASK = 0x04
#define NES_CLOCK_MASK = 0x08
#define NES_DATA_MASK = 0x10

#define AXIS_X 0x78 // x
#define AXIS_Y 0x79 // y
#define AXIS_Z 0x7a // z

// NES-Controller button map
#define NES_A 0x01
#define NES_B 0x02
#define NES_SELECT 0x04
#define NES_START 0x08
#define NES_UP 0x10
#define NES_DOWN 0x20
#define NES_LEFT 0x40
#define NES_RIGHT 0x80

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