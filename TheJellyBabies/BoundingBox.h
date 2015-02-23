#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include "stdafx.h"
#include <iostream> 

class BoundingBox
{
public:
	int x;
	int y;
	int height;
	int width;
	BoundingBox();
	BoundingBox(int m_x,int m_y,int m_width,int m_height);
	bool colision(BoundingBox bounds2);



private:
	

};
#endif