/*
 * main.h
 *
 * Copied from main.h in chr's code 
 *
 * Created: 18.09.2011 01:46:36
 *  Author: Øystein
 */ 


#ifndef MAIN_H
#define MAIN_H

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <stdlib.h>

#include "cube.h"

#define COLUMN_MASK_D 0xff
#define COLUMN_MASK_B 0x01
#define CATHODE_MASK_B 0x0e

void ioinit (void);

volatile unsigned char current_layer;

#endif