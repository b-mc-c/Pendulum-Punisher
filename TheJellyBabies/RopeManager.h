#ifndef ROPEMANAGER_H
#define ROPEMANAGER_H
#include "stdafx.h"

#include "BoundingBox.h"
#include <vector>
#include <iostream> 
#include <Box2D.h>
#include <Box2D\Dynamics\b2Body.h>
#include "Rope.h"

using namespace std;


class RopeManager
{
public:
	RopeManager();
	static void initialise(b2World& World);
	static void addRope(int level);
	
	static pair<bool,sf::Vector2f> checkEnemyCollision(BoundingBox m_shape);
	static bool checkPlayerCollision(BoundingBox m_shape);
	static bool checkPendulumCollision(BoundingBox m_shape);
	static void Update(sf::RenderWindow& Window);
	static void RemoveRopes();
	static std::vector<BoundingBox> ropeLink;
	static std::vector<BoundingBox> pendulum;
	static void addExtraRope( sf::Vector2f playerPos);

private:

	//static Rope rope;
	static const int SCALE = 32;
	//static b2World* World;
	//rope.TwoRopes(World, 500 , 0, 250, 180, SCALE);
	
	/** Prepare textures */
	//static sf::Texture pendTexture;
	//static sf::Texture ropeTexture;

};

#endif