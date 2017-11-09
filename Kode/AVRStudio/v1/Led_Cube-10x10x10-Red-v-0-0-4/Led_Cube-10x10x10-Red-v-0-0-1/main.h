/*
 * Led Cube 10x10x10 Red
 * main.h
 *
 * Created: 05.10.2011 18:43:02
 *  Author: Øystein
 */ 


#ifndef MAIN_H_
#define MAIN_H_

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <stdlib.h>


#define RCK_MASK = 0x10; // RCK mask PC5.
#define SCK_MASK = 0x20; // SCK mask PC4.

void setup(void);

volatile unsigned char current_layer;

#endif /* MAIN_H_ */