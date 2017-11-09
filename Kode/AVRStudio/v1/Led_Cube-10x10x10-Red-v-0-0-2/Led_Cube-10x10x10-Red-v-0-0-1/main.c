/*
 * Led Cube 10x10x10 Red
 * main.c
 *
 * Created: 29.09.2011 13:02:42
 *  Author: Øystein
 */ 

#include "cube.h"
#include "main.h"
#include "draw.h"
#include "effect.h"
#include "snake.h"



int main(void)
{
	// Need to seed the random function
	setup(); // Initialize IO-Ports etc.
	sei(); // Enable interrupts
    if (PIND==0x7f){ // If the down button is currently pressed play snake
		while (1)
		{snake_game();}	
	}
	else{ // Run effects
		while(1)
		{
			//effect_test1();
			//effect_test3();
			effect_stringfly2("TG!");
			effect_rain (200,80);
			effect_stars (100,70);
			effect_planboing(AXIS_X,80);
			effect_planboing(AXIS_Y,80);
			effect_planboing(AXIS_Z,80);
			effect_randfill2(800,100);
			effect_rand_planeboing_z(50, 80);
			effect_randfill (100,100);
		}
	}	
}

ISR(TIMER2_COMP_vect) // This function runs when timer2 interrupts.
{
	int i;
	PORTB = 0x00; // Turn all cathode layers off.
	PORTC &= 0xf3;
	
	PORTC &= ~0x10; // Set RCK Low.
	
	// Write data from buffer to shift registers.
	for (i=0; i<CUBE_SIZE; i++)
	{
		PORTC &= ~0x20; // Set SCK Low.
		
		PORTA = cube[current_layer][i];										// Write the first byte in the integer to Port A.
		PORTC = ((PORTC&(~0x03))|((cube[current_layer][i] & 0x0300) >> 8));	// Write the second byte in the integer to Port C.
		
		PORTC |= 0x20;  // Pull SCK High
	}
	PORTC |= 0x10;  // Pull RCK High.
	
	// Turn on the current cathode layer.
	if (current_layer<8)
	{
		PORTB = (0x01 << current_layer);
	} 
	else
	{
		PORTC |= (0x01 << (current_layer-6)); // Layer 8+9 on PC2+PC3
	}
	
	current_layer++;				// Increment the layer counter.
	if (current_layer==CUBE_SIZE)	// If we have written all the layers to the shift registers, start over.
	{
		current_layer=0;
	}
	
	snake_input(); // Take input to snake game
}

void setup(void)
{	
	DDRA = 0xff; // Columns X,Y
	DDRB = 0xff; // Layers  Z
	DDRC = 0xff; // Columns 8+9 (PC0,PC1), Layers 8+9 (PC2, PC3), SCK & RCK to shift registers X,Y (PC4,PC5), LED 1+2(PC6, PC7)
	DDRD = 0x00; // Port D 2-7 as input 
	
	PORTA = 0x00; // Turn all outputs off, just in case.
	PORTB = 0x00;
	PORTC = 0x00;
	PORTD = 0xff; // Enable pull up on PORTD
	
	
	// Setup timer 2 for interrupts
	// Frame buffer interrupt
	// 16000000/128/21 = 5952.38 interrupts per second
	// 5952.38/10 = 595 frames per second
	OCR2 = 32; 							// Interrupt counter at 20
    TCCR2 |= (1 << CS20) | (1 << CS22); // Set Clock prescaler to 128.
	TCCR2 |= (1 << WGM21);				// Set CTC mode. Reset counter when OCR2 is reached.
	TCNT2 = 0x00;						// Set initial value of counter to 0
	TIMSK |= (1 << OCIE2);				// Enable interrupt.
}