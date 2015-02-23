#ifndef BOXMANAGER_H
#define BOXMANAGER_H
#include "stdafx.h"

#include "BoundingBox.h"
#include <vector>;
#include <iostream> 

using namespace std;


class BoxManager
{
public:
	BoxManager();
	static void init();
	static void addFloor(int x, int y,int w, int h);
	static void addLadder(int x, int y,int w, int h);	
	static void addChest(int x, int y,int w, int h);
	static void addEnemyLimit(int x, int y,int w, int h);
	static void addDoor(int x, int y,int w, int h);
	static void addHook(int x, int y,int w, int h);
	static pair<bool,bool> checkFloorCollision(BoundingBox m_shape);
	static pair<bool,bool> checkChestCollision(BoundingBox m_shape);
	static bool checkLadderCollision(BoundingBox m_shape);
	static pair<bool,sf::Vector2f> checkSkyHookCollision(BoundingBox m_shape);
	static bool checkEnemyLimitCollision(BoundingBox m_shape);
	static bool checkDoorCollision(BoundingBox m_shape);
	static void clearAll();
	static void openDoor();
	static void closeDoor();
	static bool getDoor();
private:
	/*static vector<BoundingBox> floorBoxes;
	static vector<BoundingBox> ladderBoxes;*/
	static std::vector<BoundingBox> floorBoxes;
	static std::vector<BoundingBox> ladderBoxes;
	static std::vector<BoundingBox> chestBoxes;
	static std::vector<BoundingBox> enemylimitBoxes;
	static std::vector<BoundingBox> doorBoxes;
	static std::vector<BoundingBox> skyHooks;
	static bool doorOpen;

};

#endif