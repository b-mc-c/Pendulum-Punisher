#include "stdafx.h"
#ifdef _DEBUG
#pragma comment(lib,"sfml-graphics-d.lib")
#pragma comment(lib,"sfml-audio-d.lib")
#pragma comment(lib,"sfml-system-d.lib")
#pragma comment(lib,"sfml-window-d.lib")
#pragma comment(lib,"sfml-network-d.lib")
#else
#pragma comment(lib,"sfml-graphics.lib")
#pragma comment(lib,"sfml-audio.lib")
#pragma comment(lib,"sfml-system.lib")
#pragma comment(lib,"sfml-window.lib")
#pragma comment(lib,"sfml-network.lib")
#endif
#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")
#include "SFML/Graphics.hpp"
#include "SFML/OpenGL.hpp"
#include "BoundingBox.h"

using namespace std;

BoundingBox::BoundingBox()
{
	
}
BoundingBox::BoundingBox(int m_x,int m_y,int m_width,int m_height):x(m_x),y(m_y),width(m_width),height(m_height)
{

}
bool BoundingBox::colision(BoundingBox bounds2)
{
		if ((x  < bounds2.x + bounds2.width) &&
			( x + width > bounds2.x) &&
			(y + height > bounds2.y) &&
			(y < bounds2.y + bounds2.height) )
		{return true;}
		else
		{
			return false;
		}
}