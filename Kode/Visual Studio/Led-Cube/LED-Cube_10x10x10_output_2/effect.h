#ifndef EFFECT_H_
#define EFFECT_H_

#include <windows.h>
#include <mmdeviceapi.h>
#include <endpointvolume.h>
#include <Mmdeviceapi.h>

#include <iostream>

#include <cstdlib>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include "main.h"
#include "usb.h"
#include "cube.h"

public ref class Effect: public Cube{
private:

public:
	Effect(int portn, int baud):Cube(portn, baud){};
	void test1(void);
	void test2(void);
	void test3(void);
	void planboing (int plane, int speed);
	void sendvoxel_z (unsigned char x, unsigned char y, unsigned char z, int delay);
	void rand_planeboing_z(int n, int delay);
	void rain (int iterations,int delay);
	void stars (int iterations,int delay);
	void randfill (int iterations,int delay);
	void randfill2 (int iterations,int delay);
	void ball(int r, int x, int y, int z);
	void ball_grow(int delay, int startr, int stopr, int x, int y, int z);
	// From instructables 8x8x8
	void chrTest();
	void draw_cube_wireframe (vertex pnt[8]);
	void linespin (int iterations, int delay);
	void ripples (int iterations, int delay);
	void sinelines (int iterations, int delay);
	void sidewaves (int iterations, int delay);
	void spheremove (int iterations, int delay);
	void fireworks (int iterations, /*int n,*/ int delay);
	void effect_rotate_random_pixels (int iterations, int delay/*, int pixels*/);


	void peakMeter(int iterations);
	void peakMeter_rolling(int iterations);
};
// From instructables 8x8x8
/*
void effect_stringfly2(char * str);
void effect_pathmove (unsigned char *path, int length);
void effect_rand_patharound (int iterations, int delay);
void effect_pathspiral (int iterations, int delay);
void effect_path_text (int delay, char *str);
void effect_path_bitmap (int delay, char bitmap, int iterations);
*/

#endif /* EFFECT_H_ */