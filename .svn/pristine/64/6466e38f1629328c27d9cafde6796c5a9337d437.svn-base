#ifndef DRAW3D_H
#define DRAW3D_H

#include <cstdlib>

typedef struct {
	float x;
	float y;
	float z;
} vertex;

typedef struct {
    int x;
    int y;
    int z;
} intvertex;

vertex point_rotate_around_point (vertex point, vertex center, float rotation_x, float rotation_y, float rotation_z);

void rotate_cube_contents(float rx, float ry, float rz);

void calculate_cube_corners (vertex points[8], vertex center, float size);

float distance2d (float x1, float y1, float x2, float y2);

float distance3d (float x1, float y1, float z1, float x2, float y2, float z2);


#endif /* DRAW3D_H */
