/*
 * LED_Cube_3x3x3_v.0.0.1
 * main.c
 *
 * Created: 17.09.2011 22:16:51
 *  Author: Øystein
 */ 

#include <avr/io.h>

int main(void)
{
	ioinit();
    while(1)
    {
        //TODO:: Please write your application code 
    }
}


// Interrupt routine, this need heavy modification to convert from 3^3 to 8^3 cube size.
ISR(TIMER2_COMPA_vect)
{
	int i;
	int ii;
	int iii;
	PORTB &= ~CATHODE_MASK_B // Turn all cathode layers off
	
	PORTD = (cube[0][0][current_layer] << 0)
	PORTD = (cube[1][0][current_layer] << 1)
	PORTD = (cube[2][0][current_layer] << 2)
	PORTD = (cube[0][1][current_layer] << 3)
	PORTD = (cube[1][1][current_layer] << 4)
	PORTD = (cube[2][1][current_layer] << 5)
	PORTD = (cube[0][2][current_layer] << 6)
	PORTD = (cube[1][2][current_layer] << 7)
	PORTB = (cube[2][2][current_layer] << 0)
	
	// Enable the current cathode layer
	// B1 = layer 0 etc.
	PORTB = (0x01 << (current_layer+1))
	
	current_layer++;
	if (current_layer == CUBE_SIZE)
	{
		current_layer = 0 ;
	}
}
void ioinit (void)
{
	DDRD = 0xff; // Columns
	DDRB = 0x3f; // Last column B0 + cathode layers B1,B2,B3 - crystal inputs on PB6 & PB7
	
	PORTD = 0x00; // Output off
	PORTB &= 0xf0; // Output off
	
	// Setup timer 2 for interrupts
	// 16 000 000/256/21 = 2976,20 interrupts per second
	// 2976,20/3 = 992,10 "fps"
	OCR2A = 0x40; // Interrupt counter at 64
	TCCR2B |= 0x06; // Set clock prescaler to 256
	TCCR2A |= 0x02; // Set CTC mode. Reset counter when OCR2 is reached.
	TCNT2 = 0x00; // Set initial value of counter to 0
	TIMSK2 |= 0x02; // Enable interrupt.
	
}