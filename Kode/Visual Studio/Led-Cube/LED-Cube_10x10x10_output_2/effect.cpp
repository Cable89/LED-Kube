#pragma comment(lib, "ole32.lib")
#include "effect.h"

void Effect::test1(void)
{
	int i;
	for(i=0;i<CUBE_SIZE;i++)
	{
		setplane(AXIS_X, i);
		delay_ms(1000);
		clrplane(AXIS_X, i);
	}
	delay_ms(1000);
	clear();
}

void Effect::test2(void)
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

void Effect::test3(void)
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
void Effect::planboing (int plane, int speed)
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
void Effect::sendvoxel_z (unsigned char x, unsigned char y, unsigned char z, int delay)
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

void Effect::rand_planeboing_z(int n, int delay)
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
		if (!(x==a||y==b)&&getvoxel(x,y,z))
		{
			sendvoxel_z(x,y,z,delay);
		}
		a=x;b=y;
	}
	clear();
}

// As name indicates
void Effect::rain (int iterations,int delay)
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
void Effect::stars (int iterations,int delay)
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
void Effect::randfill (int iterations,int delay)
{
	for (int i=0;i<iterations;i++)
	{
		set_voxel(rand()%CUBE_SIZE,rand()%CUBE_SIZE,rand()%CUBE_SIZE);
		delay_ms(delay);
	}
	clear();
}

void Effect::randfill2(int iterations,int delay)
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

void Effect::ball(int r, int x, int y, int z){
	int rsquared = r*r;
	rsquared = rsquared + r;
	for (int i = 0; i <= r; i++){
		for (int j = 0; j <= r; j++){
			for (int k = 0; k <= r; k++){
				if (inrange(i+x,j+y,k+z) && !getvoxel(i+x,j+y,k+z) && (rsquared > (i*i+j*j+k*k))){
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

void Effect::ball_grow(int delay, int startr, int stopr, int x, int y, int z){
	for (int r=startr; r<=stopr; r++){
		ball(r,x,y,z);
		delay_ms(delay);
	}
	
}

/*
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
		set_voxel(CUBE_SIZE-1,CUBE_SIZE-1,z);
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
		set_voxel(4,0,i%8);
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
			
			for (z=7;z>-1;z--)
			{
				if ((stripe>>(7-z)) & 0x01)
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
*/
// From instructables 8x8x8
void Effect::chrTest(){
	
	int x,y,i;
	
	for (i=0;i<1000;i++){
		
		x = sin((double)i/CUBE_SIZE)*2+3.5;
		y = cos((double)i/CUBE_SIZE)*2+3.5;

		set_voxel(x,y,1);
		set_voxel(x,y,1);
		delay_ms(10);
		fill(0x0000);
	}
}

void Effect::draw_cube_wireframe (vertex pnt[8])
{
	//int i;
	
	// upper "lid"
	line_3d ((int)pnt[0].x,(int)pnt[0].y,(int)pnt[0].z,(int)pnt[1].x,(int)pnt[1].y,(int)pnt[1].z);
	line_3d ((int)pnt[2].x,(int)pnt[2].y,(int)pnt[2].z,(int)pnt[3].x,(int)pnt[3].y,(int)pnt[3].z);
	line_3d ((int)pnt[1].x,(int)pnt[1].y,(int)pnt[1].z,(int)pnt[3].x,(int)pnt[3].y,(int)pnt[3].z);
	line_3d ((int)pnt[2].x,(int)pnt[2].y,(int)pnt[2].z,(int)pnt[0].x,(int)pnt[0].y,(int)pnt[0].z);

	// lower "lid"
	line_3d ((int)pnt[4].x,(int)pnt[4].y,(int)pnt[4].z,(int)pnt[5].x,(int)pnt[5].y,(int)pnt[5].z);
	line_3d ((int)pnt[6].x,(int)pnt[6].y,(int)pnt[6].z,(int)pnt[7].x,(int)pnt[7].y,(int)pnt[7].z);
	line_3d ((int)pnt[5].x,(int)pnt[5].y,(int)pnt[5].z,(int)pnt[7].x,(int)pnt[7].y,(int)pnt[7].z);
	line_3d ((int)pnt[6].x,(int)pnt[6].y,(int)pnt[6].z,(int)pnt[4].x,(int)pnt[4].y,(int)pnt[4].z);

	// side walls
	line_3d ((int)pnt[0].x,(int)pnt[0].y,(int)pnt[0].z,(int)pnt[4].x,(int)pnt[4].y,(int)pnt[4].z);
	line_3d ((int)pnt[1].x,(int)pnt[1].y,(int)pnt[1].z,(int)pnt[5].x,(int)pnt[5].y,(int)pnt[5].z);
	line_3d ((int)pnt[2].x,(int)pnt[2].y,(int)pnt[2].z,(int)pnt[6].x,(int)pnt[6].y,(int)pnt[6].z);
	line_3d ((int)pnt[3].x,(int)pnt[3].y,(int)pnt[3].z,(int)pnt[7].x,(int)pnt[7].y,(int)pnt[7].z);

}

void Effect::linespin (int iterations, int delay)
{
	float top_x, top_y, top_z, bot_x, bot_y, bot_z, sin_base;
	float center_x, center_y;

	center_x = 4;
	center_y = 4;

	int i, z;
	for (i=0;i<iterations;i++)
	{

		//printf("Sin base %f \n",sin_base);

		for (z = 0; z < 8; z++)
		{

		sin_base = (float)i/50 + (float)z/(10+(7*sin((float)i/200)));

		top_x = center_x + sin(sin_base)*5;
		top_y = center_x + cos(sin_base)*5;
		//top_z = center_x + cos(sin_base/100)*2.5;

		bot_x = center_x + sin(sin_base+3.14)*10;
		bot_y = center_x + cos(sin_base+3.14)*10;
		//bot_z = 7-top_z;
		
		bot_z = z;
		top_z = z;

		//setvoxel((int) top_x, (int) top_y, 7);
		//setvoxel((int) bot_x, (int) bot_y, 0);

		//printf("P1: %i %i %i P2: %i %i %i \n", (int) top_x, (int) top_y, 7, (int) bot_x, (int) bot_y, 0);

		//line_3d((int) top_x, (int) top_y, (int) top_z, (int) bot_x, (int) bot_y, (int) bot_z);
		line_3d((int) top_z, (int) top_x, (int) top_y, (int) bot_z, (int) bot_x, (int) bot_y);
		}

		delay_ms(120);
		fill(0x0000);
	}

}

void Effect::sinelines (int iterations, int delay)
{
	int i,x;

	float left, right, sine_base, x_dividor,ripple_height;

	for (i=0; i<iterations; i++)
	{
		for (x=0; x<CUBE_SIZE ;x++)
		{
			x_dividor = 2 + sin((float)i/100)+1;
			ripple_height = 3 + (sin((float)i/200)+1)*6;

			sine_base = (float) i/40 + (float) x/x_dividor;

			left = 4 + sin(sine_base)*ripple_height;
			right = 4 + cos(sine_base)*ripple_height;
			right = 7-left;

			//printf("%i %i \n", (int) left, (int) right);

			line_3d(0-3, x, (int) left, 7+3, x, (int) right);
			//line_3d((int) right, 7, x);
		}
	
	delay_ms(delay);
	fill(0x0000);
	}
}

// Display a sine wave running out from the center of the cube.
void Effect::ripples (int iterations, int delay)
{
	float /*origin_x, origin_y,*/ distance, height, ripple_interval;
	int x,y,i;

	fill(0x0000);

	for (i=0;i<iterations;i++)
	{
		for (x=0;x<CUBE_SIZE;x++)
		{
			for (y=0;y<CUBE_SIZE;y++)
			{
				distance = distance2d(4.5,4.5,x,y)/9.899495*8;
				//distance = distance2d(3.5,3.5,x,y);
				ripple_interval =1.3;
				height = 5+sin(distance/ripple_interval+(float) i/50)*5;

				set_voxel(x,y,(int) height);	
			}
		}
		delay_ms(delay);
		fill(0x0000);
	}
}

void Effect::sidewaves (int iterations, int delay)
{
	float origin_x, origin_y, distance, height, ripple_interval;
	int x,y,i;

	fill(0x0000);

	for (i=0;i<iterations;i++)
	{

		origin_x = 4.5+sin((float)i/500)*4;
		origin_y = 4.5+cos((float)i/500)*4;
		
		for (x=0;x<CUBE_SIZE;x++)
		{
			for (y=0;y<CUBE_SIZE;y++)
			{
				distance = distance2d(origin_x,origin_y,x,y)/9.899495*8;
				ripple_interval =2;
				height = 5+sin(distance/ripple_interval+(float) i/50)*5;

				set_voxel(x,y,(int) height);
				set_voxel(x,y,(int) height);
					
			}
		}

		delay_ms(delay);
		fill(0x0000);
	}
}

void Effect::spheremove (int iterations, int delay)
{
	
	fill(0x00);

	float origin_x, origin_y, origin_z, distance, diameter;

	origin_x = 0;
	origin_y = 5;
	origin_z = 5;

	diameter = 3;

	int x, y, z, i;

	for (i=0; i<iterations; i++)
	{
		origin_x = 5+sin((float)i/50)*2.5;
		origin_y = 5+cos((float)i/50)*2.5;
		origin_z = 5+cos((float)i/30)*2;

		diameter = 2+sin((float)i/150);

		for (x=0; x<CUBE_SIZE; x++)
		{
			for (y=0; y<CUBE_SIZE; y++)
			{
				for (z=0; z<CUBE_SIZE; z++)
				{
					distance = distance3d(x,y,z, origin_x, origin_y, origin_z);
					//printf("Distance: %f \n", distance);

					if (distance>diameter && distance<diameter+1)
					{
						set_voxel(x,y,z);
					}
				}
			}
		}

		delay_ms(delay);
		fill(0x0000);
	}

}

void Effect::fireworks (int iterations, /*int n,*/ int delay)
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
			delay_ms(25+50*e);
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

void Effect::effect_rotate_random_pixels (int iterations, int delay/*, int pixels*/)
{
	vertex points[/*pixels*/20];
	vertex rotated[/*pixels*/20];

	float fy, fx, fz;
	int x,y,z;
	int i,p;

	float rot_x = 0;
	float rot_y = 0;
	float rot_z = 0;
	vertex cube_center = {4.5, 4.5, 4.5};

	for (i=0; i</*pixels*/20; i++)
	{
		x = rand()%1200-200;	
		y = rand()%1200-200;	
		z = rand()%1200-200;
		fx = (float)x/100;
		fy = (float)y/100;
		fz = (float)z/100;

		points[i].x = fx;
		points[i].y = fy;
		points[i].z = fz;

		set_voxel((int)points[i].x, (int)points[i].y, (int)points[i].z);
		delay_ms(10);
	}
	delay_ms(500);

	for (i=0; i<iterations; i++)
	{
		rot_x = (float)i/75;
		rot_y = (float)i/150;
		rot_z = (float)i/200;

		for (p=0; p</*pixels*/20; p++)
		{
			rotated[p] = point_rotate_around_point (points[p], cube_center, rot_x, rot_y, rot_z);
		}

		fill(0x00);
		for (p=0; p</*pixels*/20; p++)
		{
			set_voxel((int)rotated[p].x, (int)rotated[p].y, (int)rotated[p].z);
		}

		delay_ms(delay);
	}

	fill(0x0000);
}

void Effect::peakMeter(int iterations){
    //HRESULT hr;
	float meterlevel = 0.0;
	float audiolevel = 0.0;
	IMMDeviceEnumerator* pEnumerator = NULL;
	IMMDevice* pDevice = NULL;
	IAudioMeterInformation* pMeterInfo = NULL;

	CoInitialize(NULL);

	CoCreateInstance(__uuidof(MMDeviceEnumerator),NULL, CLSCTX_INPROC_SERVER,__uuidof(IMMDeviceEnumerator),(void**)&pEnumerator);

	pEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &pDevice);

	pDevice->Activate(__uuidof(IAudioMeterInformation), CLSCTX_ALL, NULL, (void**)&pMeterInfo);

	for(int i=0; i<iterations; i++){
	//while (1){
		pMeterInfo->GetPeakValue(&audiolevel);
		meterlevel = 10*audiolevel;
		cout << meterlevel << endl;
		clear();
		for(int z=0; (float)z<meterlevel; z++){
			setplane_z(z);
		}
		delay_ms(5);
	}
}

void Effect::peakMeter_rolling(int iterations){
	float meterlevel = 0.0;
	float audiolevel = 0.0;
	IMMDeviceEnumerator* pEnumerator = NULL;
	IMMDevice* pDevice = NULL;
	IAudioMeterInformation* pMeterInfo = NULL;

	CoInitialize(NULL);

	CoCreateInstance(__uuidof(MMDeviceEnumerator),NULL, CLSCTX_INPROC_SERVER,__uuidof(IMMDeviceEnumerator),(void**)&pEnumerator);

	pEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &pDevice);

	pDevice->Activate(__uuidof(IAudioMeterInformation), CLSCTX_ALL, NULL, (void**)&pMeterInfo);

	for(int i=0; i<iterations; i++){
	//while (1){
		pMeterInfo->GetPeakValue(&audiolevel);
		meterlevel = 10*audiolevel;
		cout << meterlevel << endl;
		//clrplane_y(0);
		for(int z=0; z<CUBE_SIZE; z++){
			if((float)z<meterlevel){
				set_line_x(0,z);
			}else{
				clr_line_x(0,z);
			}
		}
		delay_ms(20);
		shift (AXIS_Y, 1);
	}
}