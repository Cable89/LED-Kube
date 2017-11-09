/*
 * effect.c
 *
 * Created: 15.10.2011 17:26:09
 *  Author: Øystein
 */ 

#include "cube.h"
#include "draw.h"
#include "effect.h"
#include "font.h"

void effect_test1(void)
{
	int i;
	for(i=0;i<CUBE_SIZE;i++)
	{
		setplane (AXIS_X, i);
		delay_ms(1000);
		clrplane (AXIS_X, i);
	}
	delay_ms(1000);
	clear();
}

void effect_test2(void)
{
	int x,y,z;
	for (x=0;x<CUBE_SIZE;x++)
	{
		for (y=0;y<CUBE_SIZE;y++)
		{
			for (z=0;z<CUBE_SIZE;z++)
			{
				set_voxel(x,y,z);
				delay_ms(200);
			}
		}
	}
}

void effect_test3(void)
{
	clear();
	int x;
	for (x=0;x<CUBE_SIZE;x++)
	{
		set_voxel(x,0,0);
		delay_ms(1000);
	}
	clear();
}

// Draw a plane on one axis and send it back and forth once.
void effect_planboing (int plane, int speed)
{
	int i;
	for (i=0;i<CUBE_SIZE;i++)
	{
		clear();
        setplane(plane, i);
		delay_ms(speed);
	}
	
	for (i=CUBE_SIZE;i>=0;i--)
	{
		clear();
        setplane(plane,i);
		delay_ms(speed);
	}
	clear();
}

// Send a voxel flying from one side of the cube to the other
// If its at the bottom, send it to the top..
void sendvoxel_z (unsigned char x, unsigned char y, unsigned char z, int delay)
{
	int i, ii;
	for (i=0; i<CUBE_SIZE; i++)
	{
		if (z == CUBE_SIZE-1)
		{
			ii = CUBE_SIZE-1-i;
			clr_voxel(x,y,ii+1);
		}
		else
		{
			ii = i;
			clr_voxel(x,y,ii-1);
		}
		set_voxel(x,y,ii);
		delay_ms(delay);
	}
}

void effect_rand_planeboing_z(int n, int delay)
{
	int i,j,k,x,y,a,b;
	int z=0;
	clear();
	for (i=0;i<CUBE_SIZE;i++)
	{
		for (j=0;j<CUBE_SIZE;j++)
		{
			k = rand()%4;
			if (k>1)
			{
				set_voxel(i,j,0);
			}
		}
	}
	for (i=0;i<CUBE_SIZE;i++)
	{
		for (j=0;j<CUBE_SIZE;j++)
		{
			if (!getvoxel(i,j,0))
			{
				set_voxel(i,j,CUBE_SIZE-1);
			}
		}
	}
	for (i=0;i<n;i++)
	{
		x = rand() % CUBE_SIZE-1;
		y = rand() % CUBE_SIZE-1;
		if (z==0)
		{z=CUBE_SIZE-1;}
		else
		{z=0;}
		if (~(x==a||y==b)&&getvoxel(x,y,z))
		{
			sendvoxel_z(x,y,z,delay);
		}
		a=x;b=y;
	}
	clear();
}

// As name indicates
void effect_rain (int iterations,int delay)
{
	int i, ii;
	int rnd_x;
	int rnd_y;
	int rnd_num;
	
	for (ii=0;ii<iterations;ii++)
	{
		rnd_num = rand()%4;
		
		for (i=0; i < rnd_num;i++)
		{
			rnd_x = rand()%10;
			rnd_y = rand()%10;
			set_voxel(rnd_x,rnd_y,9);
		}
		
		delay_ms(delay);
		shift(AXIS_Z,-1);
	}
}

// Horizontal rain
void effect_stars (int iterations,int delay)
{
	int i, ii;
	int rnd_x;
	int rnd_z;
	int rnd_num;
	
	for (ii=0;ii<iterations;ii++)
	{
		rnd_num = rand()%4;
		
		for (i=0; i < rnd_num;i++)
		{
			rnd_x = rand()%10;
			rnd_z = rand()%10;
			set_voxel(rnd_x,CUBE_SIZE-1,rnd_z);
		}
		
		delay_ms(delay);
		shift(AXIS_Y,-1);
	}
}

// Fills the cube voxel for voxel at random positions
void effect_randfill (int iterations,int delay)
{
	for (int i=0;i<iterations;i++)
	{
		set_voxel(rand()%CUBE_SIZE,rand()%CUBE_SIZE,rand()%CUBE_SIZE);
		delay_ms(delay);
	}
	clear();
}

void effect_randfill2(int iterations,int delay)
{
	for (int i=0;i<iterations;i++)
	{
		set_voxel(rand()%CUBE_SIZE,rand()%CUBE_SIZE,rand()%CUBE_SIZE);
		delay_ms(delay);
		if (delay <0)
		{
			delay = 6;
		}
		else
		{
			delay -= 1;
		}
	}
	clear();
}


// From instructables 8x8x8
void effect_stringfly2(char * str)
{
	int x,y,i;
	unsigned char chr[5];
	
	while (*str)
	{
		font_getchar(*str++, chr);
		
        // Put a character on the back of the cube
		for (x = 0; x < 5; x++)
		{
			for (y = 0; y < 8; y++)
			{
				if ((chr[x] & (0x80>>y)))
				{
					set_voxel(x+2,(CUBE_SIZE-1),y);
				}
			}
		}
		
        // Shift the entire contents of the cube forward by 6 steps
        // before placing the next character
		for (i = 0; i<6; i++)
		{
			delay_ms(100);
            shift(AXIS_Y,-1);
		}
	}
    // Shift the last character out of the cube.
	for (i = 0; i<CUBE_SIZE; i++)
	{
		delay_ms(100);
        shift(AXIS_Y,-1);
	}
	
}