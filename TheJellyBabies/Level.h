#ifndef LEVEL_H
#define LEVEL_H

#include "stdafx.h"
#include "BoxManager.h"
#include <fstream>
#include "EnemyManager.h"
#include "RopeManager.h"
#include <iostream> 

class Level
{
public:
	Level();
	static void LoadLevel(string name, string texturename);
	static void loadnextlevel(float lastGameTime);
	static void draw(sf::RenderWindow& window);
	static vector<string> loadALevelFromTextFile(string name);
	static void  reloadlevel();
	static bool  levelNumber(int i);
	static bool  islevelAvaliable(int i);
	static void loadBestTimes();
	static void saveBestTimes();
	static int getStars(int levelNum);
private:        //protected if inherating
	
	static std::vector<sf::Sprite> background; //class variables
	static std::vector<int> bestTimes;
	static sf::Texture texture; //class variables
	static const int SCALE;//class variable
	static int currentlevel;
	static const int MAXLEVELS; 

};

#endif


