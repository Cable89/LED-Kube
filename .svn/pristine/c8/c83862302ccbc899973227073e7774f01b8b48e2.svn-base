/*
 * effect.c
 *
 * Created: 18.09.2011 16:06:03
 *  Author: Øystein
 */ 

// Test effect
// Set one plane at a time
void test (int n)
{
	int i;
    for (i=0; i<n; i++)
	{
		fill (0x00);
		setplane (AXIS_Z, 0);
		delay_x (500);
		clrplane (AXIS_Z, 0);
		setplane (AXIS_Z, 1);
		delay_x (500);
		clrplane (AXIS_Z, 1);
		setplane (AXIS_Z, 2);
		delay_x (500);
		clrplane (AXIS_Z, 2);
	}
}

// Test effect 2
// Flash entire cube

void test2 (int n)
{
  int i;
  for (i=0; i<n; i++)
  {
    fill(0xff);
    delay_x(500);
    fill(0x00);
    delay_x(500);
  }
}

void test3 (int n, int t)
{
	int i;
	for (i=0; i<n; i++)
	{
		fill (0x00);
		cube[0][0][0] = 0xff;delay_x(t);
		cube[1][0][0] = 0xff;delay_x(t);
		cube[2][0][0] = 0xff;delay_x(t);
        cube[0][1][0] = 0xff;delay_x(t);
		cube[1][1][0] = 0xff;delay_x(t);
		cube[2][1][0] = 0xff;delay_x(t);
        cube[0][2][0] = 0xff;delay_x(t);
		cube[1][2][0] = 0xff;delay_x(t);
		cube[2][2][0] = 0xff;delay_x(t);
        cube[0][0][1] = 0xff;delay_x(t);
		cube[1][0][1] = 0xff;delay_x(t);
		cube[2][0][1] = 0xff;delay_x(t);
        cube[0][1][1] = 0xff;delay_x(t);
		cube[1][1][1] = 0xff;delay_x(t);
		cube[2][1][1] = 0xff;delay_x(t);
        cube[0][2][1] = 0xff;delay_x(t);
		cube[1][2][1] = 0xff;delay_x(t);
		cube[2][2][1] = 0xff;delay_x(t);
        cube[0][0][2] = 0xff;delay_x(t);
		cube[1][0][2] = 0xff;delay_x(t);
		cube[2][0][2] = 0xff;delay_x(t);
        cube[0][1][2] = 0xff;delay_x(t);
		cube[1][1][2] = 0xff;delay_x(t);
		cube[2][1][2] = 0xff;delay_x(t);
        cube[0][2][2] = 0xff;delay_x(t);
		cube[1][2][2] = 0xff;delay_x(t);
		cube[2][2][2] = 0xff;delay_x(t);
		fill(0x00);delay_x(t);
	}
}

void test4 (int n)
{
	int i;
	for (i=0;i<n;i++)
	{
		fill (0x00);
		setvoxel(1,1,1);
		delay(500);
		clrvoxel(1,1,1);
		delay(500);
	}
}

// Set one plane at a time
void planemove (int n, int t, unsigned char plane)
{
	int i;
    for (i=0; i<n; i++)
	{
		fill (0x00);
		setplane (plane, 0);
		delay_x (t);
		clrplane (plane, 0);
		setplane (plane, 1);
		delay_x (t);
		clrplane (plane, 1);
		setplane (plane, 2);
		delay_x (t);
		clrplane (plane, 2);
	}
}

void planemove2 (int n, int t, unsigned char plane)
{
	int i;
    for (i=0; i<n; i++)
	{
		fill (0x00);
		setplane (plane, 0);
		setplane (plane, 2);
		delay_x (t);
		clrplane (plane, 0);
		clrplane (plane, 2);
		setplane (plane, 1);
		delay_x (t);
	}
}

void planemove3 (int n, int t)
{
	int i;
	for (i=0;i<n;i++)
	{
		fill(0x00);
		setcolumn(AXIS_Z, 0, 0, 0xff);
		delay_x(t);
		fill(0x00);
		setcolumn(AXIS_Z, 0, 1, 0xff);
		setcolumn(AXIS_Z, 1, 0, 0xff);
		delay_x(t);
		fill(0x00);
		setcolumn(AXIS_Z, 0, 2, 0xff);
		setcolumn(AXIS_Z, 1, 1, 0xff);
		setcolumn(AXIS_Z, 2, 0, 0xff);
		delay_x(t);
		fill(0x00);
		setcolumn(AXIS_Z, 2, 1, 0xff);
		setcolumn(AXIS_Z, 1, 2, 0xff);
		delay_x(t);
		fill(0x00);
		setcolumn(AXIS_Z, 2, 2, 0xff);
		delay_x(t);
	}
}

// Flashes the cube
// n = number of times
// t = speed
void flash (int n, int t)
{
  int i;
  for (i=0; i<n; i++)
  {
    fill(0xff);
    delay_x(t);
    fill(0x00);
    delay_x(t);
  }
}

// Send a voxel flying from one side of the cube to the other
// If its at the bottom, send it to the top..
void sendvoxel_z (unsigned char x, unsigned char y, unsigned char z, int delay)
{
	int i, ii;
	for (i=0; i<CUBE_SIZE; i++)
	{
		if (z == 7)
		{
			ii = 7-i;
			clrvoxel(x,y,ii+1);
		} else
		{
			ii = i;
			clrvoxel(x,y,ii-1);
		}
		setvoxel(x,y,ii);
		delay_x(delay);
	}
}

// Send all the voxels from one side of the cube to the other
// Start at z and send to the opposite side.
// Sends in random order.
void sendplane_rand_z (unsigned char z, int delay, int wait)
{
	unsigned char loop = (CUBE_SIZE*CUBE_SIZE);
	unsigned char x, y;

	fill(0x00);

	setplane_z(z);
	
	// Send voxels at random until all 16 have crossed the cube.
	while(loop)
	{
		x = rand()%4;
		y = rand()%4;
		if (getvoxel(x,y,z))
		{
			// Send the voxel flying
			sendvoxel_z(x,y,z,delay);
			delay_x(wait);
			loop--; // one down, loop-- to go. when this hits 0, the loop exits. 
		}
	}
}

// Sets vertical columns around the edges and spins them around the cube
// Maybe write a better version
void effect_spin(int n, int t)
{
	int i;
	for (i=0;i<n;i++)
	{
		fill(0x00);
		setcolumn(AXIS_Z, 0, 0, 0xff);
		setcolumn(AXIS_Z, 0, 2, 0xff);
		setcolumn(AXIS_Z, 2, 0, 0xff);
		setcolumn(AXIS_Z, 2, 2, 0xff);
		delay_x(t);
		fill(0x00);
		setcolumn(AXIS_Z, 1, 0, 0xff);
		setcolumn(AXIS_Z, 2, 1, 0xff);
		setcolumn(AXIS_Z, 1, 2, 0xff);
		setcolumn(AXIS_Z, 0, 1, 0xff);
		delay_x(t);
	}
}

void effect_spin2(int n, int t)
{
	int i;
	for (i=0;i<n;i++)
	{
		fill(0x00);
		setcolumn(AXIS_Z, 1, 1, 0xff);
		setcolumn(AXIS_Z, 0, 0, 0xff);
		setcolumn(AXIS_Z, 2, 2, 0xff);
		delay_x(t);
		fill(0x00);
		setcolumn(AXIS_Z, 1, 1, 0xff);
		setcolumn(AXIS_Z, 1, 0, 0xff);
		setcolumn(AXIS_Z, 1, 2, 0xff);
		delay_x(t);
		fill(0x00);
		setcolumn(AXIS_Z, 1, 1, 0xff);
		setcolumn(AXIS_Z, 2, 0, 0xff);
		setcolumn(AXIS_Z, 0, 2, 0xff);
		delay_x(t);
		fill(0x00);
		setcolumn(AXIS_Z, 1, 1, 0xff);
		setcolumn(AXIS_Z, 2, 1, 0xff);
		setcolumn(AXIS_Z, 0, 1, 0xff);
		delay_x(t);
		fill(0x00);
		setcolumn(AXIS_Z, 1, 1, 0xff);
		setcolumn(AXIS_Z, 2, 2, 0xff);
		setcolumn(AXIS_Z, 0, 0, 0xff);
		delay_x(t/3);
	}
}

// Turn on one random voxel at a time
void randvoxel(int n, int t)
{
	int i;
	int x, y, z;
	int a, b, c;
	for (i=0;i<n;i++)
	{
		x = rand()%CUBE_SIZE;
		y = rand()%CUBE_SIZE;
		z = rand()%CUBE_SIZE;
		if ((a!=x)|(b!=y)&(c!=z))
		{
			fill(0x00);
			setvoxel(x,y,z);
			delay_x(t);
		}
		a = x;
		b = y;
		c = z;
	}
	
}