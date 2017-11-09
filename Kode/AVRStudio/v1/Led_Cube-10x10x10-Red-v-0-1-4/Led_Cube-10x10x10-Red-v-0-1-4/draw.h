/*
 * Led Cube 10x10x10 Red
 * draw.h
 *
 * Created: 05.10.2011 18:45:03
 *  Author: Øystein
 */ 


#ifndef DRAW_H_
#define DRAW_H_

// CPU speed for delay function
# define F_CPU 16000000

#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile unsigned char current_layer;
volatile uint16_t cube[CUBE_SIZE][CUBE_SIZE]; // Cube buffer [z][y]

//void delay(uint32_t millis_delay);
void delay_ms(int x);

unsigned char inrange(int x, int y, int z);

void set_voxel(int x, int y,int z);
void clr_voxel(int x, int y, int z);
unsigned char getvoxel(int x, int y, int z);
void altervoxel(int x, int y, int z, int state);
void flipvoxel(int x, int y, int z);

void setplane (char axis, unsigned char i);
void clrplane (char axis, unsigned char i);
void setplane_x(int x);
void clrplane_x(int x);
void setplane_y(int y);
void clrplane_y(int y);
void setplane_z(int z);
void clrplane_z(int z);

void shift (char axis, int direction);

void fill (int pattern);
void clear (void);


#endif /* DRAW_H_ */