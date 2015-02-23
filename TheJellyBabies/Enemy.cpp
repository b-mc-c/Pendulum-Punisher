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
#include "Enemy.h"
#include "BoxManager.h"

#include "RopeManager.h"
Enemy::Enemy(): 
	SCALE(32),
	mleftRightSpeed(0.5f),
	MAXSPEED(7.5f * 32),
	mPosition(sf::Vector2f(29 * SCALE ,17 * SCALE)),
	mSpriteWidthAndHeight(sf::Vector2f(32,64)),
	mVelocity(sf::Vector2f(-3 * SCALE,0)),
	gravity(sf::Vector2f(0,9.81 * SCALE)),
	alive(true),	
	hit(false),
	timesincehit(0.0f)
{	
}
void Enemy::Update(float time) 
{
	SkeletonBounds_update(bounds, skeleton, true);
	drawable->update(time);
	if(alive)
	{
		if(!hit)
		{
			BoundingBox tempBounds(mPosition.x,mPosition.y,mSpriteWidthAndHeight.x,mSpriteWidthAndHeight.y);
			mbounds = tempBounds;
			pair<bool,sf::Vector2f> colision = RopeManager::checkEnemyCollision(tempBounds);
			if(colision.first)
			{
				//mPosition.x = 1000;
				mVelocity = colision.second;
				mVelocity.x *= SCALE * 2;
				mVelocity.y *= SCALE * 2;
				if(mVelocity.y > 0)
				{
					mVelocity.y *= -1;
				}
				
				hit = true;
			}
			if(BoxManager::checkEnemyLimitCollision(tempBounds))
			{
				mVelocity.x *= -1;
				mPosition.x += mVelocity.x* time + 0.5f * gravity.x * time * time;
				if(mVelocity.x < 0)
				{
					skeleton->flipX = true;
				}
				else 
				{
					skeleton->flipX = false;
				}
				
			}
			mPosition.x += mVelocity.x* time + 0.5f * gravity.x * time * time;
			mVelocity.x += gravity.x * time;
		}
		else 
		{
			
			mPosition += mVelocity* time + 0.5f * gravity * time * time;
			mVelocity += gravity * time;
			timesincehit += time;
			if (timesincehit > 1)
			{
				alive = false;
			}
		}
	}
	skeleton->x = mPosition.x + 16;
	skeleton->y = mPosition.y  + 64;
	Skeleton_updateWorldTransform(skeleton);

}
void Enemy::load()// load in images
{
	atlas = Atlas_createFromFile("data/spineboy.atlas", 0);
	json = SkeletonJson_create(atlas);
	json->scale = 0.1f;
	skeletonData = SkeletonJson_readSkeletonDataFile(json, "data/spineboy.json");
	if (!skeletonData) {
		printf("%s\n", json->error);
		exit(0);
	}
	SkeletonJson_dispose(json);
	bounds = SkeletonBounds_create();

	// Configure mixing.
	stateData = AnimationStateData_create(skeletonData);
	AnimationStateData_setMixByName(stateData, "walk", "jump", 0.2f);
	AnimationStateData_setMixByName(stateData, "jump", "run", 0.2f);
	

	drawable = new SkeletonDrawable(skeletonData, stateData);
	drawable->timeScale = 1;

	skeleton = drawable->skeleton;
	skeleton->flipX = true;
	skeleton->flipY = false;
	Skeleton_setToSetupPose(skeleton);

	skeleton->x = 32;
	skeleton->y = 64;
	Skeleton_updateWorldTransform(skeleton);
	//not sure yet
	if (false) {
		AnimationState_setAnimationByName(drawable->state, 0, "test", true);
	} else {
		AnimationState_setAnimationByName(drawable->state, 0, "walk", true);
		//AnimationState_addAnimationByName(drawable->state, 0, "jump", false, 3);
		//AnimationState_addAnimationByName(drawable->state, 0, "run", true, 0);
	}
	
	if(!texture.loadFromFile("BadMan.png"))
	{
		cout << "There was an error loading image" << endl;
	}
	
	sprite.setTexture(texture);
	
}
void Enemy::Draw(sf::RenderWindow& window)
{
	if(alive)
	{
		//sprite.setPosition(mPosition);
		//window.draw(sprite);// Draw it
		window.draw(*drawable);
	}
}
void Enemy::setPosition(sf::Vector2f pos)
{
	mPosition = pos;
}
sf::Vector2f Enemy::getPosition()
{
	return mPosition;
}
void Enemy::setVelocity(sf::Vector2f vel)
{
	mVelocity =vel;
}
sf::Vector2f Enemy::getVelocity()
{
	return mVelocity;
}
sf::FloatRect  Enemy::getBoundBox()
{
	return mBoundBox;
}
bool Enemy::Alive()
{
	return alive;
}
bool Enemy::checkcolision(BoundingBox playerBounds)
{
	return mbounds.colision(playerBounds);
}
bool Enemy::getHit()
{
	return hit;
}