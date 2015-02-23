#include <iostream>
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

#include "EnemyManager.h"
#include "BoxManager.h"
#include "Level.h"

using namespace std;
std::vector<Enemy> EnemyManager::enemies(0);
int EnemyManager::enemiesAlive = 0;

EnemyManager::EnemyManager()
{

	
}
void EnemyManager::init()
{
	
}
void EnemyManager::AddEnemy(float x, float y)
{
	Enemy temp;
	temp.setPosition(sf::Vector2f(x,y));
	enemies.push_back(temp);
	for(int i = 0 ; i< enemies.size(); i++)
	{
		enemies[i].load();
	
	}
}
void EnemyManager::draw(sf::RenderWindow& window)
{
	for(int i = 0 ; i< enemies.size(); i++)
	{
		enemies[i].Draw(window);
	}
}
void EnemyManager::LoadFromMap(string name)
{
	enemies.clear();
	vector<string> map =  Level::loadALevelFromTextFile(name);
	const int mapX = 30;
	const int mapY = 20;
	const int SCALE = 32;
	


		for (int y = 0; y < mapY; y++)
		{
			for (int x = 0; x < mapX; x++)
			{
				char c = (char)map[y][x];
		
				if (c == 'E')
				{	
		
					AddEnemy(x * SCALE,y * SCALE);
			
				}
				if (c == 'B')
				{	
		
					BoxManager::addEnemyLimit(x * SCALE, y * SCALE ,SCALE, SCALE);
			
				}
        
        
			}
		}
	}
void EnemyManager::update(float deltatime)
{
	enemiesAlive = 0;
	for (int i = 0; i < enemies.size();i++)
	{
		enemies[i].Update(deltatime);
		if (enemies[i].Alive())
		{
			enemiesAlive++;
		}
	}
	if(enemiesAlive == 0)
	{
		BoxManager::openDoor();
	}
	/*std::vector<Enemy>::iterator enemyit = enemies.begin();
	for(;enemyit != enemies.end(); enemyit++)
	{
		if(!enemyit->Alive())
		{
			enemies.erase(enemyit);
			enemyit = enemies.begin();
		}
	}*/

}
bool EnemyManager::checkcolision(BoundingBox playerBounds)
{
	for (int i = 0; i < enemies.size();i++)
	{
		if (enemies[i].checkcolision(playerBounds)&& !enemies[i].getHit())
		{
			return true;
		}
	}
	return false;
}
int EnemyManager::getEnemiesAlive(){return enemiesAlive;}