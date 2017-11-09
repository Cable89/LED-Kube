#ifndef CUBE_H_
#define CUBE_H_

#include "main.h"
#include "usb.h"
#include "draw_3d.h"

#define AXIS_X 0x78 // x
#define AXIS_Y 0x79 // y
#define AXIS_Z 0x7a // z

public ref class Cube: public Usb{
private:
	
public:
	Cube():Usb(){};
	Cube(int portn, int baud):Usb(portn, baud){};

	unsigned char inrange(int x, int y, int z);
	
	void set_voxel(int x, int y,int z);
	void clr_voxel(int x, int y, int z);
	unsigned char getvoxel(int x, int y, int z);
	void altervoxel(int x, int y, int z, int state);
	void flipvoxel(int x, int y, int z);
	
	void setplane(char axis, unsigned char i);
	void clrplane(char axis, unsigned char i);
	void setplane_x(int x);
	void clrplane_x(int x);
	void setplane_y(int y);
	void clrplane_y(int y);
	void setplane_z(int z);
	void clrplane_z(int z);
	
	void shift (char axis, int direction);

	void fill (int pattern);
	void clear (void);
	
	//From instructables 8x8x8
	void line_3d (int x1, int y1, int z1, int x2, int y2, int z2);
	void line_3d_float (vertex point1, vertex point2);

	void set_line_x(int y, int z);
	void clr_line_x(int y, int z);
};

void delay_ms(int x);

#endif /* CUBE_H_ */