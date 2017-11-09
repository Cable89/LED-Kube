/*
 * Led Cube 10x10x10 Red
 * draw.c
 *
 * This file contains the drawing functions
 *
 * Created: 06.10.2011 15:32:32
 * Author: Øystein
 */ 

#include "cube.h"
#include "draw.h"

// Check if the coordinates are inside the cube.
unsigned char inrange(int x, int y, int z)
{
	if (x>=0 && x<CUBE_SIZE && y>=0 && y<CUBE_SIZE && z>=0 && z<CUBE_SIZE)
	{
		return 1;
	} 
	else
	{
		return 0; // Not inside.
	}
}


// Set a specific voxel
void set_voxel(int x, int y,int z)
{
	if (inrange(x,y,z))
	{
		cube[z][y] |= (0x0001 << x);
	}
}

// Clear a specific voxel
void clr_voxel(int x, int y, int z)
{
	if (inrange(x,y,z))
	{
		cube[z][y] &= ~(0x0001 << x);
	}
}

// Get the current status of a voxel
unsigned char getvoxel(int x, int y, int z)
{
	if (inrange(x,y,z))
	{
		if (cube[z][y] & (1 << x))
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else
	{
		return 0;
	}		
}

// Alter the state of a voxel with a bool value
void altervoxel(int x, int y, int z, int state)
{
	if (inrange(x,y,z))
	{
		if (state == 1)
		{
			set_voxel(x,y,z);
		} 
		else
		{
			clr_voxel(x,y,z);
		}
	}
}

// Flip a voxel
void flipvoxel(int x, int y, int z)
{
	if (inrange(x,y,z))
	{
		cube[z][y] ^= (1 << x);
	}
}

// Set a specific plane along a specific axis
void setplane (char axis, unsigned char i)
{
	switch (axis)
	{
		case AXIS_X:
			setplane_x(i);
			break;
		case AXIS_Y:
			setplane_y(i);
			break;
		case AXIS_Z:
			setplane_z(i);
			break;
	}
	
}

// Clear a specific plane along a specific axis
void clrplane (char axis, unsigned char i)
{
	switch (axis)
	{
		case AXIS_X:
			clrplane_x(i);
			break;
		case AXIS_Y:
			clrplane_y(i);
			break;
		case AXIS_Z:
			clrplane_z(i);
			break;
	}
	
}


// Set a specific plane along the X-axis
void setplane_x(int x)
{
	int y;
	int z;
	if (x>=0 && x<CUBE_SIZE)
	{
		for (y=0; y<CUBE_SIZE; y++)
		{
			for (z=0; z<CUBE_SIZE; z++)
			{
				cube[z][y] |= (1 << x);
			}
		}
	}
}

// Clear a specific plane along the X-axis
void clrplane_x(int x)
{
	int y;
	int z;
	if (x>=0 && x<CUBE_SIZE)
	{
		for (y=0; y<CUBE_SIZE; y++)
		{
			for (z=0; z<CUBE_SIZE; z++)
			{
				cube[z][y] &= (~0x0001 << x);
			}
		}
	}
}

// Set a specific plane along the Y-axis
void setplane_y(int y)
{
	int z;
	if (y>=0 && y<CUBE_SIZE)
	{
		for (z=0; z<CUBE_SIZE; z++)
		{
			cube[z][y] = 0xffff;
		}		
	}
}

// Clear a specific plane along the Y-axis
void clrplane_y(int y)
{
	int z;
	if (y>=0 && y<CUBE_SIZE)
	{
		for (z=0; z<CUBE_SIZE; z++)
		{
			cube[z][y] = 0x0000;
		}		
	}
}

// Set a specific plane along the Z-axis
void setplane_z(int z)
{
	int y;
	if (z>=0 && z<CUBE_SIZE)
	{
		for (y=0; y<CUBE_SIZE; y++)
		{
			cube[z][y] = 0xffff;
		}
	}
}

// Clear a specific plane along the Z-axis
void clrplane_z(int z)
{
	int y;
	if (z>=0 && z<CUBE_SIZE)
	{
		for (y=0; y<CUBE_SIZE; y++)
		{
			cube[z][y] = 0x0000;
		}
	}
}


// Fill the cube with a pattern (fill entire cube 0xffff)
void fill (int pattern)
{
	int y;
	int z;
	for (y=0; y<CUBE_SIZE; y++)
	{
		for (z=0; z<CUBE_SIZE; z++)
		{
			cube[z][y] = pattern;
		}
	}
}

// Clear the entire cube
void clear (void)
{
	int y;
	int z;
	for (y=0; y<CUBE_SIZE; y++)
	{
		for (z=0; z<CUBE_SIZE; z++)
		{
			cube[z][y] = 0x0000;
		}
	}
}



/*
// Suggested arduino delay function
// http://code.google.com/p/arduino/issues/detail?id=237
// implemented?
void delay(uint32_t millis_delay)
{
	uint16_t micros_now = (uint16_t)micros();
	while (millis_delay > 0)
	{
		if (((uint16_t)micros() - micros_now) >= 1000)
		{
			millis_delay--;
			micros_now += 1000;
		}
	}  
}
*/

// Delay loop.
// This is not calibrated to milliseconds,
// but we had already made to many effects using this
// calibration when we figured it might be a good idea
// to calibrate it.
/*
void delay_ms(uint16_t x)
{
  uint8_t y, z;
  for ( ; x > 0 ; x--){
    for ( y = 0 ; y < 90 ; y++){
      for ( z = 0 ; z < 6 ; z++){
        asm volatile ("nop");
      }
    }
  }
}
*/

// Expanded delay function
void delay_ms(int x)
{
	for (int i=0;i<x;i++)
	{
		_delay_ms(0.8);
	}
}


void shift (char axis, int direction)
{
	int i, x ,y;
	int ii, iii;
	int state;

	for (i = 0; i < CUBE_SIZE; i++)
	{
		if (direction == -1)
		{
			ii = i;
		} else
		{
			ii = (9-i);
		}	
	
	
		for (x = 0; x < CUBE_SIZE; x++)
		{
			for (y = 0; y < CUBE_SIZE; y++)
			{
				if (direction == -1)
				{
					iii = ii+1;
				} else
				{
					iii = ii-1;
				}
				
				if (axis == AXIS_Z)
				{
					state = getvoxel(x,y,iii);
					altervoxel(x,y,ii,state);
				}
				
				if (axis == AXIS_Y)
				{
					state = getvoxel(x,iii,y);
					altervoxel(x,ii,y,state);
				}
				
				if (axis == AXIS_X)
				{
					state = getvoxel(iii,y,x);
					altervoxel(ii,y,x,state);
				}
			}
		}
	}
	
	if (direction == -1)
	{
		i = 9;
	} else
	{
		i = 0;
	}	
	
	for (x = 0; x < CUBE_SIZE; x++)
	{
		for (y = 0; y < CUBE_SIZE; y++)
		{
			if (axis == AXIS_Z)
				clr_voxel(x,y,i);
				
			if (axis == AXIS_Y)
				clr_voxel(x,i,y);
			
			if (axis == AXIS_X)
				clr_voxel(i,y,x);
		}
	}
}
