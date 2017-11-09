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
#include "usb.h"



int main(void)
{
	// Need to seed the random function
	setup(); // Initialize IO-Ports etc.
	sei(); // Enable interrupts
	nesControllerData=2;
	delay_ms(500); // give the NES-controller interrupt time to run
	while (!(UCSRA & (1<<UDRE))){
	}
	UDR = 0x01;
	
	//if (usb_mode_enable()){ // read data from usb
		usb_buffer_get();
	//}*/
    if (nesControllerData & 0x08){ // If the start button is currently pressed play snake
		while (1)
		{snake_game();}	
	}
	else{ // Run effects
		while(1)
		{
			//effect_test1();
			//effect_test3();
			effect_path_bitmap(80,0,5);
			effect_ball_grow(100, 1, 4, 4, 4, 4);
			clear();
			effect_ball_grow(100, 1, 9, 0, 9, 0);
			delay_ms(1000);
			clear();
			effect_ball_grow(100, 1, 12, 0, 0, 0);
			delay_ms(1000);
			clear();
			
			effect_path_text(120,"TG12!");
			effect_rand_patharound(50,200);
			if (nesControllerData & 0x08)
			{
				snake_game();
			}
			//effect_stringfly2("TG12!");
			effect_rain (200,80);
			effect_stars (80,70);
			clear();
			//effect_path_text(120,"ARNE!");
			clear();
			effect_planboing(AXIS_X,80);
			effect_planboing(AXIS_Y,80);
			effect_planboing(AXIS_Z,80);
			clear();
			effect_randfill2(800,100);
			clear();
			//effect_path_text(120,"SCT.OMEGA BRODERSKAB, NTNU");
			//effect_path_bitmap(80,0,5);
			effect_rand_planeboing_z(50, 80);
			clear();
			//effect_path_text(120,"LEDS ARE FUN");
			clear();
			effect_randfill (100,100);
			clear();
		}
	}	
}

void setup(void)
{	
	DDRA = 0xff; // Columns X,Y
	DDRB = 0xff; // Layers  Z
	DDRC = 0xff; // Columns 8+9 (PC0,PC1), Layers 8+9 (PC2, PC3), SCK & RCK to shift registers X,Y (PC4,PC5), LED 1+2(PC6, PC7)
	DDRD = 0x7f; // Port D (4)6-7 as input, PD0=RX, PD1=TX
	
	PORTA = 0x00; // Turn all outputs off, just in case.
	PORTB = 0x00;
	PORTC = 0x00;
	PORTD = (0xff) & ~(0x08); // Enable pull up on PORTD and supply NES-controller with 5v on PD(0)2 and GND on PD(1)3
	
	// NES-Controller
	/*	PD2 = 5V
		PD3 = GND
		PD4 = STROBE
		PD5 = CLOCK
		PD6 = DATA
	*/
	
	// FPS formula:
	// fps = F/(P*T*10)
	// F = Clock frequency [Hz]
	// P = Prescaler setting
	// T = Count to
	
	// Setup timer 2 for interrupts (LED-output)
	// Frame buffer interrupt
	// 16 000 000/128/1250 = 100 interrupts per second
	// 100/10 = 10 frames per second
	OCR2 = 1250; 						// Interrupt counter at 1250
    TCCR2 |= (1 << CS20) | (1 << CS22); // Set Clock prescaler to 128.
	TCCR2 |= (1 << WGM21);				// Set CTC mode. Reset counter when OCR2 is reached.
	TCNT2 = 0x00;						// Set initial value of counter to 0
	TIMSK |= (1 << OCIE2);				// Enable interrupt.
	
	
	// Setup timer 0 for interrupts (NES-controller)
	// 16 000 000/1024/520 = 30Hz
	OCR0 = 520;										// Interrupt counter at
	TCCR0 |= (1 << CS00) | (1 << CS01) | (1 << CS02);	// Set clock prescaler to 1024
	TCCR0 |= (1 << WGM01);								// Set CTC mode
	TCNT0 = 0x00;										// Set initial value of counter to 0
	TIMSK |= (1 << OCIE0);							// Enable interrupt on timer 0
	
	// Initiate USART
    // USART Baud rate is defined in BAUD (MYUBRR)
    UBRRH = (MYUBRR >> 8);
    UBRRL =  MYUBRR;
    // UCSRC - USART control register
    // bit 7-6      sync/async 00 = async,  01 = sync
    // bit 5-4      parity 00 = disabled
    // bit 3        stop bits 0 = 1 bit  1 = 2 bits
    // bit 2-1      frame length 11 = 8
    // bit 0        clock polarity = 0
    UCSRC  = 0b10000110;
    // Enable USART, tx and rx
    UCSRB = (1<<RXEN)|(1<<TXEN);
	while (!(UCSRA & (1<<UDRE))){
	}
    UDR = 0x00; // send an empty byte to indicate powerup.
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
	
	// snake_input(); // Take input to snake game
}

ISR(TIMER0_COMP_vect) // Read from NES-controller
{
	nesControllerData = 0x00;
	// Strobe
	PORTD |= 0x10;
	_delay_us(12);
	PORTD &= ~0x10;
	//input data
	for (int i=0; i<8; i++)
	{
		nesControllerData |= (((~PIND & 0x40) >> 6) << i); // 6 was 4
		_delay_us(6);
		PORTD |= 0x20; // Clock
		_delay_us(6);
		PORTD &= ~0x20;
	}
	// Lag snake input fra kontroller input
	if      ((nesControllerData & 0x40) && !(sdir==SOUTH))
	{sinput = NORTH;} 
	else if ((nesControllerData & 0x80) && !(sdir==NORTH))
	{sinput = SOUTH;}
	else if ((nesControllerData & 0x10) && !(sdir==WEST))
	{sinput = EAST;}
	else if ((nesControllerData & 0x20) && !(sdir==EAST))
	{sinput = WEST;}
	else if ((nesControllerData & 0x02) && !(sdir==DOWN))
	{sinput = UP;}
	else if ((nesControllerData & 0x01) && !(sdir==UP))
	{sinput = DOWN;}
	
	// NES-Controller button map
	/*	01 = A
		02 = B
		04 = SELECT
		08 = START
		10 = UP
		20 = DOWN
		40 = LEFT
		80 = RIGHT
	*/
}