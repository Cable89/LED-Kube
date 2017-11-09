/*
 * cube.h
 *
 * Created: 17.09.2011 23:31:52
 *  Author: Øystein
 */ 


#ifndef CUBE_H
#define CUBE_H

// Set the size of the cube here
#define CUBE_SIZE 3

// Cube buffer
// Data from this array is loaded onto the cube for each duty cycle
volatile unsigned char cube[CUBE_SIZE][CUBE_SIZE][CUBE_SIZE];
unsigned char bytebufferD; // LED 0,0 to 1,2
unsigned char bytebufferB; // LED 2,2 in bit 0

// Frame buffer
// Animations that take a lot of time to compute are temporarily
// stored to this array, then loaded into cube[][][] when the image
// is ready to be displayed
volatile unsigned char fb[CUBE_SIZE][CUBE_SIZE][CUBE_SIZE];

// Some effects can render on different axis
// for example send pixels along an axis
// for better readability, we use the following predefined constants
#define AXIS_X 0x78 // x
#define AXIS_Y 0x79 // y
#define AXIS_Z 0x7a // z

#endif