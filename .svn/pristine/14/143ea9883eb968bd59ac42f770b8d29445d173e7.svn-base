/*
 * usb.c
 *
 * Created: 03.05.2012 16:43:52
 *  Author: Øystein
 */ 

#include "usb.h"

void usb_buffer_get(){	
	int temp;
	int z = 0;
	int y = 0;
	
	while (1){
		// Wait until a byte has been received
		while ( !(UCSR1A & (1<<RXC1)) );
		// Load the first received byte from USB into a buffer.
		temp = UDR1;
		// Wait until the second byte has been received
		while ( !(UCSR1A & (1<<RXC1)) );
		// Load the second byte into the buffer
		temp |= (UDR1 << 8);
		
		//cube[z][y] = temp;
		y++;
		if (y == CUBE_SIZE){
			z++;
			y=0;
		}
		if (z == CUBE_SIZE){
			z=0;
			UDR1 = 42; // Indicate that the cube expects line n.0 (z=0, y=0)
		}
	}	
}