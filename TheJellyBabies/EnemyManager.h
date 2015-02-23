#ifndef ENEMYMANAGER_H
#define ENEMYMANAGER_H

#include "BoundingBox.h"
#include "Enemy.h"

#include <vector>;
#include <iostream> 



using namespace std;


class EnemyManager
{
public:
	static const int MAXENEMIES = 3;
	EnemyManager();
	static void init();
	static void AddEnemy(float x, float y);
	static std::vector<Enemy> enemies;
	static void draw(sf::RenderWindow& window);
	static void  LoadFromMap(string name);
	static void update(float deltatime);
	static int getEnemiesAlive();
	static bool checkcolision(BoundingBox playerBounds);
private:
	static int enemiesAlive;
};

#endif