#include "cube.h"

// Check if the coordinates are inside the cube.
unsigned char Cube::inrange(int x, int y, int z)
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
void Cube::set_voxel(int x, int y,int z)
{
	if (inrange(x,y,z))
	{
		// cube[z][y] |= (0x0001 << x);
		buffer[2*(y+10*z)] |= (0x01 << x);
		buffer[(2*(y+10*z))+1] |= (0x01 << (x-8));
	}
}

// Clear a specific voxel
void Cube::clr_voxel(int x, int y, int z)
{
	if (inrange(x,y,z))
	{
		//cube[z][y] &= ~(0x0001 << x);
		buffer[2*(y+10*z)] &= ~(0x01 << x);
		buffer[(2*(y+10*z))+1] &= ~(0x01 << (x-8));
	}
}

// Get the current status of a voxel
unsigned char Cube::getvoxel(int x, int y, int z){
	if (inrange(x,y,z)){
		if (buffer[2*(y+10*z)] & (1 << x) || buffer[(2*(y+10*z))+1] & (1 << (x-8))){
			return 1;
		}
	}
	return 0;		
}

// Alter the state of a voxel with a bool value
void Cube::altervoxel(int x, int y, int z, int state)
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
void Cube::flipvoxel(int x, int y, int z)
{
	if (inrange(x,y,z))
	{
		//cube[z][y] ^= (1 << x);
		buffer[2*(y+10*z)] ^= (0x01 << x);
		buffer[(2*(y+10*z))+1] ^= (0x01 << (x-8));
	}
}

// Set a specific plane along a specific axis
void Cube::setplane (char axis, unsigned char i)
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
void Cube::clrplane (char axis, unsigned char i)
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
void Cube::setplane_x(int x)
{
	int y;
	int z;
	if (x>=0 && x<CUBE_SIZE)
	{
		for (y=0; y<CUBE_SIZE; y++)
		{
			for (z=0; z<CUBE_SIZE; z++)
			{
				//cube[z][y] |= (1 << x);
				buffer[2*(y+10*z)] |= (0x01 << x);
				buffer[(2*(y+10*z))+1] |= (0x01 << (x-8));
			}
		}
	}
}

// Clear a specific plane along the X-axis
void Cube::clrplane_x(int x)
{
	int y;
	int z;
	if (x>=0 && x<CUBE_SIZE)
	{
		for (y=0; y<CUBE_SIZE; y++)
		{
			for (z=0; z<CUBE_SIZE; z++)
			{
				//cube[z][y] &= (~0x0001 << x);
				buffer[2*(y+10*z)] &= ~(0x01 << x);
				buffer[(2*(y+10*z))+1] &= ~(0x01 << (x-8));
			}
		}
	}
}

// Set a specific plane along the Y-axis
void Cube::setplane_y(int y)
{
	int z;
	if (y>=0 && y<CUBE_SIZE)
	{
		for (z=0; z<CUBE_SIZE; z++)
		{
			//cube[z][y] = 0xffff;
			buffer[2*(y+10*z)] = 0xff;
			buffer[(2*(y+10*z))+1] = 0xff;
		}		
	}
}

// Clear a specific plane along the Y-axis
void Cube::clrplane_y(int y)
{
	int z;
	if (y>=0 && y<CUBE_SIZE)
	{
		for (z=0; z<CUBE_SIZE; z++)
		{
			//cube[z][y] = 0x0000;
			buffer[2*(y+10*z)] = 0x00;
			buffer[(2*(y+10*z))+1] = 0x00;
		}		
	}
}

// Set a specific plane along the Z-axis
void Cube::setplane_z(int z)
{
	int y;
	if (z>=0 && z<CUBE_SIZE)
	{
		for (y=0; y<CUBE_SIZE; y++)
		{
			//cube[z][y] = 0xffff;
			buffer[2*(y+10*z)] = 0xff;
			buffer[(2*(y+10*z))+1] = 0xff;
		}
	}
}

// Clear a specific plane along the Z-axis
void Cube::clrplane_z(int z)
{
	int y;
	if (z>=0 && z<CUBE_SIZE)
	{
		for (y=0; y<CUBE_SIZE; y++)
		{
			//cube[z][y] = 0x0000;
			buffer[2*(y+10*z)] = 0x00;
			buffer[(2*(y+10*z))+1] = 0x00;
		}
	}
}


// Fill the cube with a pattern (fill entire cube 0xffff)
void Cube::fill (int pattern)
{
	int y;
	int z;
	for (y=0; y<CUBE_SIZE; y++)
	{
		for (z=0; z<CUBE_SIZE; z++)
		{
			//cube[z][y] = pattern;
			buffer[2*(y+10*z)] = pattern;
			buffer[(2*(y+10*z))+1] = (pattern >> 8);
		}
	}
}

// Clear the entire cube
void Cube::clear (void)
{
	int y;
	int z;
	for (y=0; y<CUBE_SIZE; y++)
	{
		for (z=0; z<CUBE_SIZE; z++)
		{
			//cube[z][y] = 0x0000;
			buffer[2*(y+10*z)] = 0x00;
			buffer[(2*(y+10*z))+1] = 0x00;
		}
	}
}


//// Expanded delay function
//void delay_ms(int x)
//{
//	for (int i=0;i<x;i++)
//	{
//		_delay_ms(1);
//	}
//}

// Delay function for win32

void delay_ms(int x){
	System::Threading::Thread::Sleep(x);
}


void Cube::shift (char axis, int direction)
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


// From instructables 8x8x8
void Cube::line_3d (int x1, int y1, int z1, int x2, int y2, int z2)
{
	int i, dx, dy, dz, l, m, n, x_inc, y_inc, z_inc,
	err_1, err_2, dx2, dy2, dz2;
	int pixel[3];
	pixel[0] = x1;
	pixel[1] = y1;
	pixel[2] = z1;
	dx = x2 - x1;
	dy = y2 - y1;
	dz = z2 - z1;
	x_inc = (dx < 0) ? -1 : 1;
	l = abs(dx);
	y_inc = (dy < 0) ? -1 : 1;
	m = abs(dy);
	z_inc = (dz < 0) ? -1 : 1;
	n = abs(dz);
	dx2 = l << 1;
	dy2 = m << 1;
	dz2 = n << 1;
	if ((l >= m) && (l >= n)) {
	err_1 = dy2 - l;
	err_2 = dz2 - l;
	for (i = 0; i < l; i++) {
	//PUT_PIXEL(pixel);
	set_voxel(pixel[0],pixel[1],pixel[2]);
	//printf("Setting %i %i %i \n", pixel[0],pixel[1],pixel[2]);
	if (err_1 > 0) {
	pixel[1] += y_inc;
	err_1 -= dx2;
	}
	if (err_2 > 0) {
	pixel[2] += z_inc;
	err_2 -= dx2;
	}
	err_1 += dy2;
	err_2 += dz2;
	pixel[0] += x_inc;
	}
	} else if ((m >= l) && (m >= n)) {
	err_1 = dx2 - m;
	err_2 = dz2 - m;
	for (i = 0; i < m; i++) {
	//PUT_PIXEL(pixel);
	set_voxel(pixel[0],pixel[1],pixel[2]);
	//printf("Setting %i %i %i \n", pixel[0],pixel[1],pixel[2]);
	if (err_1 > 0) {
	pixel[0] += x_inc;
	err_1 -= dy2;
	}
	if (err_2 > 0) {
	pixel[2] += z_inc;
	err_2 -= dy2;
	}
	err_1 += dx2;
	err_2 += dz2;
	pixel[1] += y_inc;
	}
	} else {
	err_1 = dy2 - n;
	err_2 = dx2 - n;
	for (i = 0; i < n; i++) {
	set_voxel(pixel[0],pixel[1],pixel[2]);
	//printf("Setting %i %i %i \n", pixel[0],pixel[1],pixel[2]);
	//PUT_PIXEL(pixel);
	if (err_1 > 0) {
	pixel[1] += y_inc;
	err_1 -= dz2;
	}
	if (err_2 > 0) {
	pixel[0] += x_inc;
	err_2 -= dz2;
	}
	err_1 += dy2;
	err_2 += dx2;
	pixel[2] += z_inc;
	}
	}
	set_voxel(pixel[0],pixel[1],pixel[2]);
	//printf("Setting %i %i %i \n", pixel[0],pixel[1],pixel[2]);
	//PUT_PIXEL(pixel);
}


void Cube::line_3d_float (vertex point1, vertex point2)
{
	float x1, y1, z1, x2, y2, z2;

	x1 = point1.x;
	y1 = point1.y;
	z1 = point1.z;
	x2 = point2.x;
	y2 = point2.y;
	z2 = point2.z;


	float i;
	float dx, dy, dz, l, m, n, x_inc, y_inc, z_inc,
	err_1, err_2, dx2, dy2, dz2;
	float pixel[3];
	pixel[0] = x1;
	pixel[1] = y1;
	pixel[2] = z1;
	dx = x2 - x1;
	dy = y2 - y1;
	dz = z2 - z1;
	x_inc = (dx < 0) ? -1 : 1;
	l = abs(dx);
	y_inc = (dy < 0) ? -1 : 1;
	m = abs(dy);
	z_inc = (dz < 0) ? -1 : 1;
	n = abs(dz);
	dx2 = l*l;
	dy2 = m*m;
	dz2 = n*n;
	if ((l >= m) && (l >= n)) {
		err_1 = dy2 - l;
		err_2 = dz2 - l;
		for (i = 0; i < l; i++) {
			//PUT_PIXEL(pixel);
			set_voxel((int)pixel[0],(int)pixel[1],(int)pixel[2]);
			//printf("Setting %i %i %i \n", pixel[0],pixel[1],pixel[2]);
			if (err_1 > 0) {
				pixel[1] += y_inc;
				err_1 -= dx2;
			}
			if (err_2 > 0) {
				pixel[2] += z_inc;
				err_2 -= dx2;
			}
			err_1 += dy2;
			err_2 += dz2;
			pixel[0] += x_inc;
		}
	} else if ((m >= l) && (m >= n)) {
		err_1 = dx2 - m;
		err_2 = dz2 - m;
		for (i = 0; i < m; i++) {
			//PUT_PIXEL(pixel);
			//setvoxel(pixel[0]/scale,pixel[1]/scale,pixel[2]/scale);
			set_voxel((int)pixel[0],(int)pixel[1],(int)pixel[2]);
			//printf("Setting %i %i %i \n", pixel[0],pixel[1],pixel[2]);
			if (err_1 > 0) {
				pixel[0] += x_inc;
				err_1 -= dy2;
			}
			if (err_2 > 0) {
				pixel[2] += z_inc;
				err_2 -= dy2;
			}
			err_1 += dx2;
			err_2 += dz2;
			pixel[1] += y_inc;
		}
	} else {
		err_1 = dy2 - n;
		err_2 = dx2 - n;
		for (i = 0; i < n; i++) {
			//setvoxel(pixel[0]/scale,pixel[1]/scale,pixel[2]/scale);
			set_voxel((int)pixel[0],(int)pixel[1],(int)pixel[2]);
			//printf("Setting %i %i %i \n", pixel[0],pixel[1],pixel[2]);
			//PUT_PIXEL(pixel);
			if (err_1 > 0) {
				pixel[1] += y_inc;
				err_1 -= dz2;
			}
			if (err_2 > 0) {
				pixel[0] += x_inc;
				err_2 -= dz2;
			}
			err_1 += dy2;
			err_2 += dx2;
			pixel[2] += z_inc;
		}
	}
	//setvoxel(pixel[0]/scale,pixel[1]/scale,pixel[2]/scale);
			set_voxel((int)pixel[0],(int)pixel[1],(int)pixel[2]);
	//printf("Setting %i %i %i \n", pixel[0],pixel[1],pixel[2]);
	//PUT_PIXEL(pixel);
}

void Cube::set_line_x(int y, int z){
	buffer[2*(y+10*z)] |= 0xff;
	buffer[(2*(y+10*z))+1] |= 0xff;
}

void Cube::clr_line_x(int y, int z){
	buffer[2*(y+10*z)] &= 0x00;
	buffer[(2*(y+10*z))+1] &= 0x00;
}