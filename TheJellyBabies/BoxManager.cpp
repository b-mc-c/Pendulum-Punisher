
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

#include "BoxManager.h"
//using namespace std;


std::vector<BoundingBox> BoxManager::floorBoxes(0);
std::vector<BoundingBox> BoxManager::ladderBoxes(0);
std::vector<BoundingBox> BoxManager::chestBoxes(0);
std::vector<BoundingBox> BoxManager::enemylimitBoxes(0);
std::vector<BoundingBox> BoxManager::doorBoxes(0);
std::vector<BoundingBox> BoxManager::skyHooks(0);
bool BoxManager::doorOpen = false;

BoxManager::BoxManager()
{
}
void BoxManager::init()
{
	doorOpen = false;
}
void BoxManager::clearAll()
{
	floorBoxes.clear();
	ladderBoxes.clear();
	chestBoxes.clear();
	doorBoxes.clear();
	enemylimitBoxes.clear();
	skyHooks.clear();
}
void BoxManager::addFloor(int x, int y,int w, int h)
{
	BoundingBox temp(x,y,w,h);
	
	floorBoxes.push_back(temp);
}
void BoxManager::addHook(int x, int y,int w, int h)
{
	BoundingBox temp(x,y,w,h);
	
	skyHooks.push_back(temp);
}
void BoxManager::addChest(int x, int y,int w, int h)
{
	BoundingBox temp(x,y,w,h);
	
	chestBoxes.push_back(temp);
}
void BoxManager::addLadder(int x, int y,int w, int h)
{
	BoundingBox temp(x,y,w,h);
	
	ladderBoxes.push_back(temp);

}
void BoxManager::addDoor(int x, int y,int w, int h)
{
	BoundingBox temp(x,y,w,h);
	
	doorBoxes.push_back(temp);
	doorOpen = false;

}
void BoxManager::openDoor(){doorOpen = true;}
void BoxManager::closeDoor(){doorOpen = false;}
bool BoxManager::getDoor(){return doorOpen;}
void BoxManager::addEnemyLimit(int x, int y,int w, int h)
{
	BoundingBox temp(x,y,w,h);
	
	enemylimitBoxes.push_back(temp);

}

//void BoxManager::addTorch(int x, int y,int w, int h)
//{
//	//BoundingBox temp(x,y,w,h);
//	
//	//ladderBoxes.push_back(temp);
//
//}

 pair<bool,bool> BoxManager::checkFloorCollision(BoundingBox m_shape)
 {
	 pair<bool,bool> result(false,false);
	 for(int i=0; i < floorBoxes.size(); i++)
	 {
		if ((m_shape.x + 1 < floorBoxes[i].x + floorBoxes[i].width) &&
	(m_shape.x + m_shape.width -2 > floorBoxes[i].x) &&
	(m_shape.y + m_shape.height > floorBoxes[i].y) &&
	(m_shape.y < floorBoxes[i].y + floorBoxes[i].height) )
	{			
		
		result.first =true;
		if(m_shape.y + (m_shape.height/5 * 4) < floorBoxes[i].y)
		{
			result.second = true;//if result. second == true we are above the floor
		}
		return result;
		}
	 }
	 return result;
 }
 pair<bool,bool> BoxManager::checkChestCollision(BoundingBox m_shape)
 {
	 pair<bool,bool> result(false,false);
	 for(int i=0; i < chestBoxes.size(); i++)
	 {
		if ((m_shape.x + 1 < chestBoxes[i].x + chestBoxes[i].width) &&
	(m_shape.x + m_shape.width -2 > chestBoxes[i].x) &&
	(m_shape.y + m_shape.height > chestBoxes[i].y) &&
	(m_shape.y < chestBoxes[i].y + chestBoxes[i].height) )
	{			
		
		result.first =true;
		if(m_shape.y + (m_shape.height/5 * 4) < chestBoxes[i].y)
		{
			result.second = true;//if result. second == true we are above the floor
		}
		return result;
		}
	 }
	 return result;
 }
 bool BoxManager::checkLadderCollision(BoundingBox m_shape)
 {
	  for(int i=0; i < ladderBoxes.size(); i++)
	 {
		if ((m_shape.x < ladderBoxes[i].x + ladderBoxes[i].width) &&
		(m_shape.x + m_shape.width > ladderBoxes[i].x) &&
		(m_shape.y + m_shape.height > ladderBoxes[i].y) &&
		(m_shape.y < ladderBoxes[i].y + ladderBoxes[i].height) )
		{			
		
		
			return true;
		}
	 }
	 return false;
 }
  bool BoxManager::checkEnemyLimitCollision(BoundingBox m_shape)
 {
	  for(int i=0; i < enemylimitBoxes.size(); i++)
	 {
		if ((m_shape.x < enemylimitBoxes[i].x + enemylimitBoxes[i].width) &&
	(m_shape.x + m_shape.width > enemylimitBoxes[i].x) &&
	(m_shape.y + m_shape.height > enemylimitBoxes[i].y) &&
	(m_shape.y < enemylimitBoxes[i].y + enemylimitBoxes[i].height) )
	{			
		
		
		return true;
		}
	 }
	 return false;
 }
   bool BoxManager::checkDoorCollision(BoundingBox m_shape)
 {
	 if(doorOpen)
	 {
	  for(int i=0; i < doorBoxes.size(); i++)
	 {
		if ((m_shape.x < doorBoxes[i].x + doorBoxes[i].width) &&
	(m_shape.x + m_shape.width > doorBoxes[i].x) &&
	(m_shape.y + m_shape.height > doorBoxes[i].y) &&
	(m_shape.y < doorBoxes[i].y + doorBoxes[i].height) )
	{			
		
		
		return true;
		}
	 }
	 return false;
	 }
	 else
	 {
		  return false;
	 }
 }
pair<bool,sf::Vector2f> BoxManager::checkSkyHookCollision(BoundingBox m_shape)
{
	for(int i=0; i < skyHooks.size(); i++)
	{
		if(skyHooks[i].colision(m_shape))
		{
			return make_pair(true,sf::Vector2f(skyHooks[i].x + skyHooks[i].width/2,skyHooks[i].y+ skyHooks[i].height/2));
		}
	}
	return make_pair(false,sf::Vector2f(0,0));
}