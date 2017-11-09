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
#include <math.h>

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
	
	for (i=(CUBE_SIZE-2);i>=0;i--)
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
	//clear();
}


// From instructables 8x8x8
void effect_stringfly2(char * str)
{
	int x,z,i;
	unsigned char chr[5];
	
	while (*str)
	{
		font_getchar(*str++, chr);
		
        // Put a character on the back of the cube
		for (x = 0; x < 5; x++)
		{
			for (z = 0; z < 8; z++)
			{
				if ((chr[x] & (0x80>>z)))
				{
					set_voxel(x+2,(CUBE_SIZE-1),z);
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

// From instructables 8x8x8
void effect_pathmove (unsigned char *path, int length)
{
	int i,z;
	unsigned char state;
	
	for (i=(length-1);i>=1;i--)
	{
		for (z=0;z<CUBE_SIZE;z++)
		{
			
			state = getvoxel(((path[(i-1)]>>4) & 0x0f), (path[(i-1)] & 0x0f), z);
			altervoxel(((path[i]>>4) & 0x0f), (path[i] & 0x0f), z, state);
		}
	}
	for (i=0;i<CUBE_SIZE;i++)
	clr_voxel(((path[0]>>4) & 0x0f), (path[0] & 0x0f),i);
}

// From instructables 8x8x8
void effect_rand_patharound (int iterations, int delay)
{
	int z, dz, i;
	z = 4;
	unsigned char path[36];
	
	font_getpath(0,path,36);
	
	for (i = 0; i < iterations; i++)
	{
		dz = ((rand()%3)-1);
		z += dz;
		
		if (z>CUBE_SIZE-1)
			z = CUBE_SIZE-1;
			
		if (z<0)
			z = 0;
		
		effect_pathmove(path, 36);
		set_voxel(CUBE_SIZE,CUBE_SIZE,z);
		delay_ms(delay);
	}
}

// From instructables 8x8x8
void effect_pathspiral (int iterations, int delay)
{
	int z, i;
	z = 4;
	unsigned char path[16];
	
	font_getpath(1,path,16);
	
	for (i = 0; i < iterations; i++)
	{
		set_voxel(z,0,i%8);
		delay_ms(delay);
		effect_pathmove(path, 28);
		
	}
}

// From instructables 8x8x8
void effect_path_text (int delay, char *str)
{
	int z, i,ii;
	z = 4;
	unsigned char path[36];
	font_getpath(0,path,36);
	
	unsigned char chr[5];
	unsigned char stripe;
	
	while (*str)
	{
		//charfly(*str++, direction, axis, mode, delay);
		
		
		font_getchar(*str++, chr);
		
		for (ii=0;ii<5;ii++)
		{
			//stripe = pgm_read_byte(&font[(chr*5)+ii]);
			stripe = chr[ii];
			
			for (z=8;z>0;z--)
			{
				if ((stripe>>(8-z)) & 0x01)
				{
					set_voxel(CUBE_SIZE-1,CUBE_SIZE-1,z);
				} else
				{
					clr_voxel(CUBE_SIZE-1,CUBE_SIZE-1,z);
				}
				
			}
			effect_pathmove(path, 36);
			delay_ms(delay);
		}
	
		effect_pathmove(path, 36);
		delay_ms(delay);
	}
	for (i=0;i<28;i++)
	{
		effect_pathmove(path, 36);
		delay_ms(delay);
	}
}
/*
// From instructables 8x8x8
void effect_path_bitmap (int delay, char bitmap, int iterations)
{
	int z, i, ii;
	z = 4;
	unsigned char path[36];
	font_getpath(0,path,36);
	
	for (i=0; i < iterations; i++)
	{	
		for (ii=0;ii<8;ii++)
		{		
			for (z=0;z<8;z++)
			{
				if (font_getbitmappixel(bitmap,(7-z),ii))
				{
					set_voxel(CUBE_SIZE-1,CUBE_SIZE-1,z);
				} else
				{
					clr_voxel(CUBE_SIZE-1,CUBE_SIZE-1,z);
				}
				
			}
			delay_ms(delay);
			effect_pathmove(path, 36);
		}
	
		for (ii=0;ii<29;ii++)
		{
			delay_ms(delay);
			effect_pathmove(path, 36);
		}
	}
	for (ii=0;ii<10;ii++)
	{
		delay_ms(delay);
		effect_pathmove(path, 36);
	}
}
*/

// From instructables 8x8x8
void effect_path_bitmap (int delay, char bitmap, int iterations)
{
	int z, i, ii;
	z = 4;
	unsigned char path[36];
	font_getpath(0,path,36);
	
	for (i=0; i < iterations; i++)
	{
		for (ii=0;ii<CUBE_SIZE;ii++)
		{
			for (z=0;z<CUBE_SIZE;z++)
			{
				if (font_getbigbitmappixel(bitmap,(CUBE_SIZE-1-z),ii))
				{
					set_voxel(CUBE_SIZE-1,CUBE_SIZE-1,z);
				} else
				{
					clr_voxel(CUBE_SIZE-1,CUBE_SIZE-1,z);
				}
				
			}
			delay_ms(delay);
			effect_pathmove(path, 36);
		}
		
		for (ii=0;ii<26;ii++)
		{
			delay_ms(delay);
			effect_pathmove(path, 36);
		}
	}
	for (ii=0;ii<10;ii++)
	{
		delay_ms(delay);
		effect_pathmove(path, 36);
	}
}


void effect_ball(int r, int x, int y, int z){
	int rsquared = r*r;
	rsquared = rsquared + r;
	for (int i = 0; i <= r; i++){
		for (int j = 0; j <= r; j++){
			for (int k = 0; k <= r; k++){
				if (inrange(i+x,j+y,k+z) && !getvoxel(i+x,j+y,k+z) && (rsquared > pow((i),2)+pow((j),2)+pow(k,2))){
					set_voxel(x+i,y+j,z+k);
					set_voxel(x-i,y+j,z+k);
					set_voxel(x+i,y-j,z+k);
					set_voxel(x-i,y-j,z+k);
					set_voxel(x+i,y+j,z-k);
					set_voxel(x-i,y+j,z-k);
					set_voxel(x+i,y-j,z-k);
					set_voxel(x-i,y-j,z-k);
				}
			}
		}
	}
}

void effect_ball_grow(int delay, int startr, int stopr, int x, int y, int z){
	for (int r=startr; r<=stopr; r++){
		effect_ball(r,x,y,z);
		delay_ms(delay);
	}
	
}

void effect_fireworks (int iterations, /*int n,*/ int delay)
{
	fill(0x0000);

	int i,f,e;

	float origin_x = 3;
	float origin_y = 3;
	float origin_z = 3;

	int rand_y, rand_x, rand_z;

	float slowrate, gravity;

	// Particles and their position, x,y,z and their movement, dx, dy, dz
	float particles[/*n*/50][6];

	for (i=0; i<iterations; i++)
	{

		origin_x = rand()%5;
		origin_y = rand()%5;
		origin_z = rand()%2;
		origin_z +=6;
		origin_x +=2;
		origin_y +=2;

		// shoot a particle up in the air
		for (e=0;e<origin_z;e++)
		{
			set_voxel(origin_x,origin_y,e);
			delay_ms(1+50*e);
			fill(0x0000);
		}

		// Fill particle array
		for (f=0; f</*n*/50; f++)
		{
			// Position
			particles[f][0] = origin_x;
			particles[f][1] = origin_y;
			particles[f][2] = origin_z;
			
			rand_x = rand()%200;
			rand_y = rand()%200;
			rand_z = rand()%200;

			// Movement
			particles[f][3] = 1-(float)rand_x/100; // dx
			particles[f][4] = 1-(float)rand_y/100; // dy
			particles[f][5] = 1-(float)rand_z/100; // dz
		}

		// explode
		for (e=0; e<25; e++)
		{
			slowrate = 1+tan((e+0.1)/20)*10;
			
			gravity = tan((e+0.1)/20)/2;

			for (f=0; f</*n*/50; f++)
			{
				particles[f][0] += particles[f][3]/slowrate;
				particles[f][1] += particles[f][4]/slowrate;
				particles[f][2] += particles[f][5]/slowrate;
				particles[f][2] -= gravity;

				set_voxel(particles[f][0],particles[f][1],particles[f][2]);


			}

			delay_ms(delay);
			fill(0x0000);
		}

	}

}

//from instructables 8x8x8
void effect_axis_updown_randsuspend (char axis, int delay, int sleep, int invert)
{
	unsigned char positions[CUBE_SIZE*CUBE_SIZE];
	unsigned char destinations[CUBE_SIZE*CUBE_SIZE];

	int i,px;
	
	// Set 100 random positions
	for (i=0; i<(CUBE_SIZE*CUBE_SIZE); i++)
	{
		positions[i] = 0; // Set all starting positions to 0
		destinations[i] = rand()%CUBE_SIZE;
	}

	// Loop 10 times to allow destination 9 to reach all the way
	for (i=0; i<CUBE_SIZE; i++)
	{
		// For every iteration, move all position one step closer to their destination
		for (px=0; px<CUBE_SIZE*CUBE_SIZE; px++)
		{
			if (positions[px]<destinations[px])
			{
				positions[px]++;
			}
		}
		// Draw the positions and take a nap
		draw_positions_axis (axis, positions,invert);
		delay_ms(delay);
	}
	
	// Set all destinations to 7 (opposite from the side they started out)
	for (i=0; i<(CUBE_SIZE*CUBE_SIZE); i++)
	{
		destinations[i] = (CUBE_SIZE-1);
	}
	
	// Suspend the positions in mid-air for a while
	delay_ms(sleep);
	
	// Then do the same thing one more time
	for (i=0; i<CUBE_SIZE; i++)
	{
		for (px=0; px<(CUBE_SIZE*CUBE_SIZE); px++)
		{
			if (positions[px]<destinations[px])
			{
				positions[px]++;
			}
			if (positions[px]>destinations[px])
			{
				positions[px]--;
			}
		}
		draw_positions_axis (axis, positions,invert);
		delay_ms(delay);
	}
}

void draw_positions_axis (char axis, unsigned char positions[64], int invert)
{
	int x, y, p;
	
	fill(0x00);
	
	for (x=0; x<CUBE_SIZE; x++)
	{
		for (y=0; y<CUBE_SIZE; y++)
		{
			if (invert)
			{
				p = ((CUBE_SIZE-1)-positions[(x*CUBE_SIZE)+y]);
			} else
			{
				p = positions[(x*CUBE_SIZE)+y];
			}
			
			if (axis == AXIS_Z)
			set_voxel(x,y,p);
			
			if (axis == AXIS_Y)
			set_voxel(x,p,y);
			
			if (axis == AXIS_X)
			set_voxel(p,y,x);
		}
	}
	
}