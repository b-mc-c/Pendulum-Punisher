
#ifndef ENEMY_H
#define ENEMY_H

#include <iostream> 
#include "BoundingBox.h"

#include <spine/spine-sfml.h>
using namespace std;
using namespace spine;


class Enemy
{
public:
	Enemy();
	void load();// load in images
	void Update(float time);
	void Draw(sf::RenderWindow& window);
	void setPosition(sf::Vector2f pos);
	sf::Vector2f getPosition();
	void setVelocity(sf::Vector2f vel);
	sf::Vector2f getVelocity();
	sf::FloatRect  getBoundBox();
	bool checkcolision(BoundingBox playerBounds);
	bool Alive();
	bool getHit();

private:	
	int SCALE;
	bool alive;
	bool hit;
	float timesincehit;
	float MAXSPEED;
	sf::Vector2f gravity; 
	sf::Vector2f mPosition;// the position of the entity
	sf::Vector2f mVelocity;// the velocity of the enitity
	sf::Vector2f mSpriteWidthAndHeight;// stores the width of the sprite to be drawn in the x value and the height in the y value
	sf::FloatRect mBoundBox;// Xposition, Yposition , Width ,Height
	BoundingBox mbounds;
	sf::Sprite sprite;// Create a sprite
	sf::Texture texture;
	float mleftRightSpeed;
	Atlas* atlas; 
	SkeletonJson* json;
	SkeletonData *skeletonData;
	SkeletonBounds* bounds;
	AnimationStateData* stateData;
	SkeletonDrawable* drawable;
	Skeleton* skeleton;


};

#endif