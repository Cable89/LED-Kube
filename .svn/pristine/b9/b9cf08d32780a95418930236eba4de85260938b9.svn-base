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
		test(); 
    }
}


// Interrupt routine, this need heavy modification to convert from 3^3 to 8^3 cube size.
ISR(TIMER2_COMPA_vect)
{

	int i;
	int ii;
	int n = 0;
	
	PORTB &= ~CATHODE_MASK_B // Turn all cathode layers off
	/*
	for (i=0; i<3; i++)
	{
		for (ii=0; ii<3; ii++)
		{
			if (cube[ii][i][current_layer] >= 1)
			{
				PORTD |= (1 << n);
			} 
			else
			{
				PORTD &= (0 << n);
			}
			n++;
		}
	}*/
	
	if (cube[0][0][current_layer] >= 1)
	{
		PORTD |= 0x01;
	} 
	else
	{
		PORTD &= 0xfe;
	}
	
	if (cube[1][0][current_layer] >= 1)
	{
		PORTD |= 0x02;
	} 
	else
	{
		PORTD &= 0xfd;
	}
	
	if (cube[2][0][current_layer] >= 1)
	{
		PORTD |= 0x04;
	} 
	else
	{
		PORTD &= 0xfb;
	}
	
	if (cube[0][1][current_layer] >= 1)
	{
		PORTD |= 0x08 ;
	} 
	else
	{
		PORTD &= 0xf7;
	}
	
	if (cube[1][1][current_layer] >= 1)
	{
		PORTD |= 0x10;
	} 
	else
	{
		PORTD &= 0xef;
	}
	
	if (cube[2][1][current_layer] >= 1)
	{
		PORTD |= 0x20;
	} 
	else
	{
		PORTD &= 0xdf;
	}
	
	if (cube[0][2][current_layer] >= 1)
	{
		PORTD |= 0x40;
	} 
	else
	{
		PORTD &= 0xbf;
	}
	
	if (cube[1][2][current_layer] >= 1)
	{
		PORTD |= 0x80;
	} 
	else
	{
		PORTD &= 0x7f;
	}
	
	if (cube[2][2][current_layer] >= 1)
	{
		PORTB |= 0x01;
	} 
	else
	{
		PORTB &= 0x00;
	}

	// Enable the current cathode layer
	// B1 = layer 0 etc.
	PORTB = (0x01 << (current_layer+1))
	
	current_layer++;
	if (current_layer == CUBE_SIZE)
	{
		current_layer = 0;
	}
}
void ioinit (void)
{
	DDRD = 0xff;	// Columns
	DDRB = 0x1f;	// Last column B0 + cathode layers B1,B2,B3, led on B4,
					//button on B5 - crystal inputs on PB6 & PB7
	
	PORTD = 0x00;	// Output off
	PORTB &= 0xe0;	// Output off
	
	// Setup timer 2 for interrupts
	// 16 000 000/256/21 = 2976,20 interrupts per second
	// 2976,20/3 = 992,10 "fps"
	TCCR2A = 0x00;	// Reset registers(just in case)
	TCCR2B = 0x00;
	OCR2A = 0x40;	// Interrupt counter at 64
	TCCR2B |= 0x06; // Set clock prescaler to 256
	TCCR2A |= 0x02; // Set CTC mode. Reset counter when OCR2 is reached.
	TCNT2 = 0x00;	// Set initial value of counter to 0
	TIMSK2 |= 0x02; // Enable interrupt.
}

void bootseed (void)
{
	// Get random seed here, possibly some more stuff
}