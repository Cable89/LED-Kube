/*
 * usb.c
 *
 * Created: 03.05.2012 16:43:52
 *  Author: Øystein
 */ 
#include "usb.h"
#include "draw.h"

char usb_mode_enable(){
	char temp;
	while(1){
		while ( !(UCSRA & (1<<RXC)) );
		temp = UDR;
		if (temp == 0x00){
			return 1;
		}else{
			return 0;
		}
	}
	
}

void usb_buffer_get(){	
	uint16_t temp;
	int z = 0;
	int y = 0;
	
	UDR = 0x00;
	
	while (1){
		// Wait until a byte has been received
		while ( !(UCSRA & (1<<RXC)) );
		// Load the first received byte from USB into a buffer.
		temp = UDR;
		// Wait until the second byte has been received
		while ( !(UCSRA & (1<<RXC)) );
		// Load the second byte into the buffer
		temp |= (UDR << 8);
		// Echo data back
		// UDR = temp;
		
		// Load the temp buffer into the frame buffer
		cube[z][y] = temp;
		y++;
		if (y == CUBE_SIZE){
			z++;
			y=0;
		}
		if (z == CUBE_SIZE){
			z=0;
			UDR = 42; // Indicate that the cube expects line n.0 (z=0, y=0)
		}
	}	
}