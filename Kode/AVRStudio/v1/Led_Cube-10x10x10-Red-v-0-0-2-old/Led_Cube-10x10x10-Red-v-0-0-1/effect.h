/*
 * effect.h
 *
 * Created: 15.10.2011 17:25:55
 *  Author: Øystein
 */ 


#ifndef EFFECT_H_
#define EFFECT_H_

#include <stdlib.h>

void effect_test1(void);
void effect_test2(void);
void effect_test3(void);
void effect_planboing (int plane, int speed);
void sendvoxel_z (unsigned char x, unsigned char y, unsigned char z, int delay);
void effect_rand_planeboing_z(int n, int delay);
void effect_rain (int iterations,int delay);
void effect_stars (int iterations,int delay);
void effect_randfill (int iterations,int delay);
void effect_randfill2 (int iterations,int delay);
// From instructables 8x8x8
void effect_stringfly2(char * str);


#endif /* EFFECT_H_ */