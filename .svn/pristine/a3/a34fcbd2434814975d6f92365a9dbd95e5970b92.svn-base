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

/*
// Red led on D2
#define LED_RED 0x04
// Green led D3
#define LED_GREEN 0x08
// Program led on D4
#define LED_PGM 0x10;
// Leds connected to port D
#define LED_PORT PORTD
// Rs232 button on D5
#define RS232_BTN 0x20
// Main button on B4
#define MAIN_BTN 0x10 
*/

void ioinit (void);
//void bootmsg (void);

volatile unsigned char current_layer;
//volatile unsigned char pgm_mode;
//void rs232(void);
//unsigned int bootwait (void);



#endif