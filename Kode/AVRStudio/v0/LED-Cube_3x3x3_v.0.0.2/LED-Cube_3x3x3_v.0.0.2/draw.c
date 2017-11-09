/*
 * draw.c
 *
 * This file contains the draw functions
 *
 * Created: 17.09.2011 23:25:43
 *  Author: Øystein
 */ 

// This function checks if the x,y,z coordinates is inside the defined cube
unsigned char inrange(int x, int y, int z)
{
	if (x >= 0 && x < CUBE_SIZE && y >= 0 && y < CUBE_SIZE && z >= 0 && z < CUBE_SIZE)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

 // Set a single voxel to ON
void setvoxel(int x, int y, int z)
{
	if (inrange(x,y,z))
		cube[x][y][z] = 0xff;
}

// Set a single voxel to OFF
void clrvoxel(int x, int y, int z)
{
	if (inrange(x,y,z))
		cube[x][y][z] = 0;
}

 // Set a single voxel in the temp buffer to ON
void tmpsetvoxel(int x, int y, int z)
{
	if (inrange(x,y,z))
		fb[x][y][z] = 1;
}

// Set a single voxel in the temp buffer to OFF
void tmpclrvoxel(int x, int y, int z)
{
	if (inrange(x,y,z))
		fb[x][y][z] = 0;
}

// Get the current status of a voxel
unsigned char getvoxel(int x, int y, int z)
{
	if (inrange(x,y,z))
	{
		if(cube[x][y][z] == 1)
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

// In some effect we want to just take bool and write it to a voxel
// this function calls the appropriate voxel manipulation function.
void altervoxel(int x, int y, int z, int state)
{
	if (state == 1)
	{
		setvoxel(x,y,z);
	} else
	{
		clrvoxel(x,y,z);
	}
}

// Flip the state of a voxel.
// If the voxel is 1, its turned into a 0, and vice versa.
// (This function uses the bitwise XOR operator, not really
// an inverting operator but works as one when operand b is 1)
void flpvoxel(int x, int y, int z)
{
	if (inrange(x, y, z))
		cube[x][y][z] ^= 1;
}

// Assign a value to a z-plane
/*
void assignplane_z (int z, unsigned char value)
{
	int x;
	int y;
	if (z >= 0 && z < CUBE_SIZE)
	{
		for (x=0; x<CUBE_SIZE; x++)
		{
			for (y=0; y<CUBE_SIZE; y++)
			{
				cube[x][y][z] = value;
			}
		}	
	}
}
*/

// Sets a column
void setcolumn_x(int y, int z, unsigned char fill)
{
	int x=0;
	if (inrange(x, y, z))
	{
		for (x=0;x<CUBE_SIZE;x++)
		{
			cube[x][y][z] |= fill;
		}
	}
	
}

void setcolumn_y(int x, int z, unsigned char fill)
{
	int y=0;
	if (inrange(x, y, z))
	{
		for (y=0;y<CUBE_SIZE;y++)
		{
			cube[x][y][z] |= fill;
		}
	}
	
}

void setcolumn_z(int x, int y, unsigned char fill)
{
	int z=0;
	if (inrange(x, y, z))
	{
		for (z=0;z<CUBE_SIZE;z++)
		{
			cube[x][y][z] |= fill;
		}
	}
	
}

void setcolumn (char axis, int i, int ii, unsigned char fill)
{
    switch (axis)
    {
        case AXIS_X:
            setcolumn_y(i, ii, fill);
            break;
        
       case AXIS_Y:
            setcolumn_y(i, ii, fill);
            break;

       case AXIS_Z:
            setcolumn_z(i, ii, fill);
            break;
    }
}

// Sets all voxels along a given x-plane
void setplane_x (int x)
{
	int y;
	int z;
	if (x>=0 && x<CUBE_SIZE)
	{
		for (y=0;y<CUBE_SIZE;y++)
		{
			for (z=0;z<CUBE_SIZE;z++)
			{
				cube[x][y][z] |= 0xff;
			}
		}
	}
}

// Clears all voxels along a given x-plane
void clrplane_x (int x)
{
	int y;
	int z;
	if (x>=0 && x<CUBE_SIZE)
	{
		for (y=0;y<CUBE_SIZE;y++)
		{
			for (z=0;z<CUBE_SIZE;z++)
			{
				cube[x][y][z] &= 0x00;
			}
		}	
	}
}

// Sets all voxels along a given y-plane
void setplane_y (int y)
{
	int x;
	int z;
	if (y >= 0 && y < CUBE_SIZE)
	{
		for (x=0; x<CUBE_SIZE; x++)
		{
			for (z=0; z<CUBE_SIZE; z++)
			{
				cube[x][y][z] |= 0xff;
			}
		}	
	}
}

// Clears all voxels along a given y-plane
void clrplane_y (int y)
{
	int x;
	int z;
	if (y >= 0 && y < CUBE_SIZE)
	{
		for (x=0; x<CUBE_SIZE; x++)
		{
			for (z=0; z<CUBE_SIZE; z++)
			{
				cube[x][y][z] &= 0x00;
			}
		}	
	}
}

// Sets all voxels along a given z-plane
void setplane_z (int z)
{
	int x;
	int y;
	if (z >= 0 && z < CUBE_SIZE)
	{
		for (x=0; x<CUBE_SIZE; x++)
		{
			for (y=0; y<CUBE_SIZE; y++)
			{
				cube[x][y][z] |= 0xff;
			}
		}	
	}
}

// Clears all voxels along a given z-plane
void clrplane_z (int z)
{
	int x;
	int y;
	if (z >= 0 && z < CUBE_SIZE)
	{
		for (x=0; x<CUBE_SIZE; x++)
		{
			for (y=0; y<CUBE_SIZE; y++)
			{
				cube[x][y][z] &= 0x00;
			}
		}	
	}
}

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

void fill (unsigned char i)
{
	int x;
	int y;
	int z;
	if (z >= 0 && z < CUBE_SIZE)
	{
		for (x=0; x<CUBE_SIZE; x++)
		{
			for (y=0; y<CUBE_SIZE; y++)
			{
				for (z=0; z<CUBE_SIZE; z++)
				{
					cube[x][y][z] = i;
				}
			}
		}	
	}
}

void tmpfill (unsigned char value)
{
	int x;
	int y;
	int z;
	if (z >= 0 && z < CUBE_SIZE)
	{
		for (x=0; x<CUBE_SIZE; x++)
		{
			for (y=0; y<CUBE_SIZE; y++)
			{
				for (z=0; z<CUBE_SIZE; z++)
				{
					fb[x][y][z] = value;
				}
			}
		}	
	}
}

// Copies the contents of fb (temp cube buffer) into the rendering buffer
void tmp2cube (void)
{	
    memcpy(cube, fb, 64); // copy the current cube into a buffer.
}

// Shift the entire contents of the cube along an axis
// This is great for effects where you want to draw something
// on one side of the cube and have it flow towards the other
// side. Like rain flowing down the Z axis.
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
			ii = (7-i);
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
		i = 7;
	} else
	{
		i = 0;
	}	
	
	for (x = 0; x < CUBE_SIZE; x++)
	{
		for (y = 0; y < CUBE_SIZE; y++)
		{
			if (axis == AXIS_Z)
				clrvoxel(x,y,i);
				
			if (axis == AXIS_Y)
				clrvoxel(x,i,y);
			
			if (axis == AXIS_X)
				clrvoxel(i,y,x);
		}
	}
}

// Delay loop.
// This is not calibrated to milliseconds,
// but we had already made to many effects using this
// calibration when we figured it might be a good idea
// to calibrate it.
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

// Suggested arduino delay function
// http://code.google.com/p/arduino/issues/detail?id=237
// implemented?
void delay_x(uint32_t millis_delay)
{
  uint16_t micros_now = (uint16_t)micros();

  while (millis_delay > 0) {
    if (((uint16_t)micros() - micros_now) >= 1000) {
      millis_delay--;
      micros_now += 1000;
    }
  }  
}