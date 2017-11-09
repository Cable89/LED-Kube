#include "draw_3d.h"
#include <cmath>


vertex point_rotate_around_point (vertex point, vertex center, float rotation_x, float rotation_y, float rotation_z)
{
	float x, y, z;
	float sx,cx, sy,cy, sz,cz;
	float xy,xz, yx,yz, zx,zy;
	vertex newpoint;

	// Center all the points around 0,0,0
	x = point.x - center.x;
	y = point.y - center.y;
	z = point.z - center.z;

	// Precalculate sinus and cosinus for each axis rotation
	sx = sin(rotation_x);
	cx = cos(rotation_x);

	sy = sin(rotation_y);
	cy = cos(rotation_y);

	sz = sin(rotation_z);
	cz = cos(rotation_z);


	// Rotation around x
	xy = cx*y - sx*z;
	xz = sx*y + cx*z;
	
	// Rotation around y
	yz = cy*xz - sy*x;
	yx = sy*xz + cy*x;
	
	// Rotation around z
	zx = cz*yx - sz*xy;
	zy = sz*yx + cz*xy;

	newpoint.x = zx + center.x;
	newpoint.y = zy + center.y;
	newpoint.z = yz + center.z;


	return newpoint;
}


// Calculate all 8 corners of a cube.
void calculate_cube_corners (vertex pnt[8], vertex center, float size)
{

	// Distance from center on any axis.
	float dist = size/2;

	// Points
	// X				Y				Z

	pnt[0].x = center.x+dist;	pnt[0].y = center.y+dist;	pnt[0].z = center.z+dist;	// 0 right, front, upper
	pnt[1].x = center.x-dist;	pnt[1].y = center.y+dist;	pnt[1].z = center.z+dist;	// 1 left, front, upper
	pnt[2].x = center.x+dist;	pnt[2].y = center.y-dist;	pnt[2].z = center.z+dist;	// 2 right, back, upper
	pnt[3].x = center.x-dist;	pnt[3].y = center.y-dist;	pnt[3].z = center.z+dist;	// 3 left, back, uppper
	pnt[4].x = center.x+dist;	pnt[4].y = center.y+dist;	pnt[4].z = center.z-dist;	// 4 right, front, lower
	pnt[5].x = center.x-dist;	pnt[5].y = center.y+dist;	pnt[5].z = center.z-dist;	// 5 left, front, lower
	pnt[6].x = center.x+dist;	pnt[6].y = center.y-dist;	pnt[6].z = center.z-dist;	// 6 right, back, lower
	pnt[7].x = center.x-dist;	pnt[7].y = center.y-dist;	pnt[7].z = center.z-dist;	// 7 left, bakc, lower


}

float distance2d (float x1, float y1, float x2, float y2)
{	
	float dist;
	dist = sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));

	return dist;
}

float distance3d (float x1, float y1, float z1, float x2, float y2, float z2)
{	
	float dist;
	dist = sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2) + (z1-z2)*(z1-z2));

	return dist;
}