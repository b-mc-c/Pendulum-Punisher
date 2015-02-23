#ifndef ENTITY_H
#define ENTITY_H

#include <spine/spine-sfml.h>
#include "Level.h"
using namespace std;
using namespace spine;

class Entity
{
public:
	Entity();
	void load();// load in images
	bool Update(float time);
	void Draw(sf::RenderWindow& window);
	void setPosition(sf::Vector2f pos);
	sf::Vector2f getPosition();
	void setVelocity(sf::Vector2f vel);
	sf::Vector2f getVelocity();
	sf::FloatRect  getBoundBox();
	void KeyboardInputs();
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();
	float getGameTime();
	void updateState(int setTo);
protected:	
	const int SCALE;
	const float MAXSPEED;
	bool mCanMoveDown;
	bool mCanMoveUp;
	bool mCanMoveLeft;
	bool mCanMoveRight;
	bool visible;
	sf::Vector2f gravity; 
	sf::Vector2f mPosition;// the position of the entity
	sf::Vector2f mVelocity;// the velocity of the enitity
	sf::Vector2f mSpriteWidthAndHeight;// stores the width of the sprite to be drawn in the x value and the height in the y value
	sf::FloatRect mBoundBox;// Xposition, Yposition , Width ,Height
	sf::Sprite sprite;// Create a sprite
	sf::Texture texture;
	float mleftRightSpeed;
	float mJumpSpeed;
	Atlas* atlas; 
	SkeletonJson* json;
	SkeletonData *skeletonData;
	SkeletonBounds* bounds;
	AnimationStateData* stateData;
	SkeletonDrawable* drawable;
	Skeleton* skeleton;
	bool ctrlPressed;
	bool ctrlPressedaddrope;
	float gameTime;
	sf::Font font;
	int RUN , IDLE ,CLIMB,State;
};



#endif

