

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
#include <SFML/Window/Mouse.hpp>
#include "SFML/OpenGL.hpp"
#include <iostream> 
#include <string.h>
#include "Entity.h"
#include "EnemyManager.h"
#include "BoxManager.h"
#include "BoundingBox.h"
#include "RopeManager.h"
#include <stdio.h>

Entity::Entity():
	SCALE(32),
	mleftRightSpeed(0.5f),
	MAXSPEED(7.5f * 32),
	visible(true),
	ctrlPressed(false),
	ctrlPressedaddrope(false),
	gameTime(0),
	RUN(0),
	IDLE(1),
	CLIMB(2),
	State(1)
{
	mPosition = sf::Vector2f(29 * SCALE ,17 * SCALE);
	mSpriteWidthAndHeight = sf::Vector2f(32,64);
	mVelocity = sf::Vector2f(0,0);
	gravity = sf::Vector2f(0,9.81 * SCALE);
	mCanMoveDown = true;
	mCanMoveUp = false;
	mCanMoveLeft = false;
	mCanMoveRight = false;
	mJumpSpeed = 4.5f;
	

}
void Entity::load()// load in images
{

	if(!font.loadFromFile("arial.ttf"))
	{
		cout << "font did not load" << endl;
	}
	atlas = Atlas_createFromFile("data/ourHero.atlas", 0);
	json = SkeletonJson_create(atlas);
	json->scale = 0.1f;
	skeletonData = SkeletonJson_readSkeletonDataFile(json, "data/ourHero.json");
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
		//AnimationState_setAnimationByName(drawable->state, 0, "test", true);
		AnimationState_setAnimationByName(drawable->state, 0, "idle", true);
		//AnimationState_addAnimationByName(drawable->state, 0, "jump", false, 3);
		//AnimationState_addAnimationByName(drawable->state, 0, "run", true, 0);
	}

	if(!texture.loadFromFile("man.png"))
	{
		cout << "There was an error loading image" << endl;
	}
	
	sprite.setTexture(texture);
	//sprite.scale(sf::Vector2f(sprite.getScale().x / mSpriteWidthAndHeight.x, sprite.getScale().y / mSpriteWidthAndHeight.y));
}
bool Entity::Update(float time)
{	

	gameTime += time;
	cout << gameTime << endl;
	SkeletonBounds_update(bounds, skeleton, true);
	drawable->update(time);
	BoundingBox tempBounds(mPosition.x,mPosition.y,mSpriteWidthAndHeight.x,mSpriteWidthAndHeight.y);
	if(EnemyManager::checkcolision(tempBounds) && visible)
	{
		cout << "reload called" << endl;
		
		Level::reloadlevel();
		setPosition(sf::Vector2f(29 * SCALE ,17 * SCALE));
	}
	else
	{
		bool climbing = false;
		pair<bool,bool> floorcolision(BoxManager::checkFloorCollision(tempBounds));
		pair<bool,bool> chestcolision(BoxManager::checkChestCollision(tempBounds));
		bool nextLevel = BoxManager::checkDoorCollision(tempBounds);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			RopeManager::checkPlayerCollision(tempBounds);
		}
		if((sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)||sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))  && chestcolision.first)
		{
			if(!ctrlPressed)
			{
				
				visible = !visible;
				ctrlPressed = true;
			}
		}
		else
		{
			ctrlPressed = false;
		}
		pair<bool,sf::Vector2f> skyhooksCollide = BoxManager::checkSkyHookCollision(tempBounds);
		if (visible){
			if((sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)||sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))&& skyhooksCollide.first)
			{
				if(!ctrlPressedaddrope)
				{
						//add a rope 
					RopeManager::addExtraRope(skyhooksCollide.second);
					ctrlPressedaddrope = true;
				}
			}
			else
			{
				ctrlPressedaddrope = false;
			}
			
			if(chestcolision.first && chestcolision.second)//we are coliding above the floor
			{		
				mCanMoveDown = false;
				mVelocity.y= 0;
				gravity.y = 0;	
			}
			else
			{
				mCanMoveDown = true;
			}
			if(floorcolision.first && floorcolision.second)//we are coliding above the floor
			{		
				mCanMoveDown = false;
				mVelocity.y= 0;
				gravity.y = 0;		
			}
			else
			{
				mCanMoveDown = true;
			}
			if(BoxManager::checkLadderCollision(tempBounds))
			{
				mCanMoveUp = true;
				gravity.y = 0;
				if(!floorcolision.first && !chestcolision.first)
				{
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
					{
						mCanMoveDown = true;
						moveDown();
						updateState(CLIMB);
						climbing = true;
					}
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				{
					mCanMoveUp = true;
					moveUp();
					updateState(CLIMB);
					climbing = true;
			
				}
			}
			else
			{
				if(!floorcolision.first && !chestcolision.first)
				{
					gravity.y = 9.81 * SCALE;
				}
			}
			KeyboardInputs();
			if (mPosition.x < 0)
			{
				mPosition.x += 0.5f;
				mCanMoveLeft = false;
				mVelocity.x =0;
			}		
			else if (mPosition.x + mSpriteWidthAndHeight.x > 960)
			{
				mPosition.x -= 0.5f;
				mCanMoveRight = false;
				mVelocity.x =0;
			}
	
			if (mPosition.y < 0)
			{
				mCanMoveUp = false;
				mVelocity.y = 0;
			}
			if( mCanMoveUp)
			{
				if (mVelocity.y < 0)
				{
					mPosition.y += mVelocity.y* time + 0.5f * gravity.y * time * time;
					mVelocity.y += gravity.y * time;
				}
			}
			if(mCanMoveDown)
			{
				if(mVelocity.y >= 0)
				{
				mPosition.y += mVelocity.y* time + 0.5f * gravity.y * time * time;
				mVelocity.y += gravity.y * time;
				}
			}
			if(mCanMoveLeft || mCanMoveRight)
			{
				
				mPosition.x += mVelocity.x* time + 0.5f * gravity.x * time * time;
				mVelocity.x += gravity.x * time;
				mCanMoveRight = false;
				mCanMoveLeft = false;
				if(!climbing)
				{
					updateState(RUN);
				}
			}
			else 
			{
				if(mVelocity.y ==0)
				{
					updateState(IDLE);
				}
				
			}
			//cout << mVelocity.x << endl;
			if (mPosition.y + mSpriteWidthAndHeight.y > 638)
			{
				mCanMoveDown = false;
				mCanMoveUp =false;
				mVelocity.y = 0;
			}

			skeleton->x = mPosition.x + 16;
			skeleton->y = mPosition.y  + 64;
			Skeleton_updateWorldTransform(skeleton);
		}
		return nextLevel;
	}
	return false;
}
void Entity::Draw(sf::RenderWindow& window)
{
	//sprite.setPosition(mPosition);
	sf::Color col = sf::Color::White;
	// Create a text
	int temp = floorf(gameTime * 10);
	sf::Text text(std::to_string(temp * 0.1), font);
	text.setCharacterSize(40);
	text.setPosition(sf::Vector2f(window.getSize().x / 2,0));
	text.setStyle(sf::Text::Bold);
	text.setColor(col);
	window.draw(text);
	//window.draw(sprite);// Draw it
	if(visible)
	{
		window.draw(*drawable);
	}
}
void Entity::setPosition(sf::Vector2f pos)
{
	mPosition = pos;
	gameTime = 0;
	AnimationState_setAnimationByName(drawable->state, 0, "idle", true);
}
sf::Vector2f Entity::getPosition()
{
	return mPosition;
}
void Entity::setVelocity(sf::Vector2f vel)
{
	mVelocity =vel;
}
sf::Vector2f Entity::getVelocity()
{
	return mVelocity;
}
sf::FloatRect  Entity::getBoundBox()
{
	return mBoundBox;
}
void Entity::moveLeft()
{
	skeleton->flipX = true;
	if(mVelocity.x > 0)
	{
		mVelocity.x =0;
	}
	mCanMoveLeft = true;
	if (mVelocity.x > -MAXSPEED)
	{
		mVelocity.x -= mleftRightSpeed * SCALE;
	}
	//AnimationState_addAnimationByName(drawable->state, 0, "run", true, 0);
}
void Entity::moveRight()
{
	skeleton->flipX = false;
	mCanMoveRight = true;
	if(mVelocity.x < 0)
	{
		mVelocity.x =0;
	}
	if (mVelocity.x < MAXSPEED)
	{
	mVelocity.x += mleftRightSpeed * SCALE;
	}
	//AnimationState_addAnimationByName(drawable->state, 0, "run", true, 0);
}
void Entity::moveUp()
{
	mCanMoveUp= true;
	mVelocity.y = -mJumpSpeed * SCALE;
}
void Entity::moveDown()
{
	mCanMoveDown = true;
	mVelocity.y = mJumpSpeed * SCALE;
}
void Entity::KeyboardInputs()
{
	
if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
{
    // left key is pressed: move our character
	moveLeft();
  
}
else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
{
	moveRight();
}
else
{
	setVelocity(sf::Vector2f(0,mVelocity.y));
}
if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
{
	
	if(mVelocity.y ==0 )
	{
		//AnimationState_addAnimationByName(drawable->state, 0, "jump", false,0);
		
		moveUp();
		mCanMoveUp = true;
	}
}



}
float Entity::getGameTime()
{
	return gameTime;
}
void Entity::updateState(int setTo)
{
	if (State != setTo)//if the state is the same as the current state then we dont change the state
	{
		State = setTo;
		if(setTo == RUN)
		{
			AnimationState_setAnimationByName(drawable->state, 0, "run", true);
		}
		else if(setTo == IDLE)
		{
			AnimationState_setAnimationByName(drawable->state, 0, "idle", true);
			
		}
		else if(setTo == CLIMB)
		{
			AnimationState_setAnimationByName(drawable->state, 0, "climb", true);
		}

	}

}