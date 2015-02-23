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
#include "RopeManager.h"
//using namespace std;



std::vector<BoundingBox> ropeLink;
std::vector<BoundingBox> pendulum;
sf::Texture pendTexture;
sf::Texture ropeTexture;
Rope rope;
b2World* World;

RopeManager::RopeManager()
{

}
void RopeManager::initialise(b2World& world)
{
	World = &world;
	ropeTexture.loadFromFile("box.png");
	pendTexture.loadFromFile("chandelier.png");
	rope.TwoRopes(*World, 500 , 0,/*1st ropes anchorPos*/ 300, 200,/*2nd ropes anchorPos*/17 ,10, SCALE);
}
void RopeManager::addRope(int level)
{
	if (level == 0)
	{
		rope.TwoRopes(*World, 500 , 0,/*1st ropes anchorPos*/ 300, 200,/*2nd ropes anchorPos*/17 ,10, SCALE);
		pendTexture.loadFromFile("chandelier.png");
		ropeTexture.loadFromFile("box.png");
	
	}
	if(level == 1)
	{
		rope.TwoRopes(*World, 0 , 0,/*1st ropes anchorPos*/ 300, 0,/*2nd ropes anchorPos*/10 ,12, SCALE);
		rope.TwoRopes(*World, 448 , 288,/*1st ropes anchorPos*/ 800, 320,/*2nd ropes anchorPos*/6 ,14, SCALE);
		pendTexture.loadFromFile("log.png");
		ropeTexture.loadFromFile("vine.png");
	}
	if(level == 2)
	{
		rope.TwoRopes(*World, 224, 256,/*1st ropes anchorPos*/ 800, 192,/*2nd ropes anchorPos*/18 ,15, SCALE);
		pendTexture.loadFromFile("ball.png");
		ropeTexture.loadFromFile("chain.png");
	}
	if(level == 3)
	{
		rope.TwoRopes(*World, 352, 16,/*1st ropes anchorPos*/ 416, 175,/*2nd ropes anchorPos*/7 ,4, SCALE);
		pendTexture.loadFromFile("ball.png");
		ropeTexture.loadFromFile("chain.png");
	}
	if(level == 4)
	{
		rope.TwoRopes(*World, 0, 0,/*1st ropes anchorPos*/ 128, 0,/*2nd ropes anchorPos*/5 ,8, SCALE);
		pendTexture.loadFromFile("snowball.png");
		ropeTexture.loadFromFile("chain.png");
	}
}
bool RopeManager::checkPlayerCollision(BoundingBox m_shape)
{
	  for (b2Body* BodyIterator = World->GetBodyList(); BodyIterator != 0; BodyIterator = BodyIterator->GetNext())
        {
			if (BodyIterator->GetType() == b2_dynamicBody && (int)BodyIterator->GetUserData() != 1)
            {

				BoundingBox temp(SCALE * BodyIterator->GetPosition().x, SCALE * BodyIterator->GetPosition().y, 8 , 32 );
				if ((m_shape.x < temp.x + temp.width) &&
					(m_shape.x + m_shape.width > temp.x) &&
					(m_shape.y + m_shape.height > temp.y) &&
					(m_shape.y < temp.y + temp.height) )
				{
					//rope.cutRope();
					if(!World->IsLocked())
					World->DestroyBody(BodyIterator);
					BodyIterator = World->GetBodyList();
					break;
				}

			}
			else if(BodyIterator->GetType() == b2_staticBody)
			{
			}
			
	  }
	return true;
}
void RopeManager::addExtraRope( sf::Vector2f playerPos)
{
        rope.addRope(*World, playerPos);
}
 pair<bool,sf::Vector2f> RopeManager::checkEnemyCollision(BoundingBox m_shape)
 {
	 pair<bool,sf::Vector2f> result(false,sf::Vector2f(0,0));
	 for (b2Body* BodyIterator = World->GetBodyList(); BodyIterator != 0; BodyIterator = BodyIterator->GetNext())
        {
			if ((int)BodyIterator->GetUserData() == 1)
            {
				BoundingBox temp(SCALE * BodyIterator->GetPosition().x, SCALE * BodyIterator->GetPosition().y, 8 , 32 );
				if ((m_shape.x < temp.x + temp.width) &&
					(m_shape.x + m_shape.width > temp.x) &&
					(m_shape.y + m_shape.height > temp.y) &&
					(m_shape.y < temp.y + temp.height) )
				{
					result.first = true;
					b2Vec2 vel = BodyIterator->GetLinearVelocity();
					result.second = sf::Vector2f(vel.x,vel.y);
					return result;			
				}
			}
	 }
	 return result;
 }
 bool RopeManager::checkPendulumCollision(BoundingBox m_shape)
 {
	 return true;
 }
 void RopeManager::RemoveRopes()
 {
	 for (b2Body* BodyIterator = World->GetBodyList(); BodyIterator != 0; BodyIterator = BodyIterator->GetNext())
        {
			

			
			if(!World->IsLocked())
			{
				World->DestroyBody(BodyIterator);
				//BodyIterator->SetUserData(NULL);
				//BodyIterator = NULL;
			}
			
			BodyIterator = World->GetBodyList();
	 }
 }
 void RopeManager::Update(sf::RenderWindow& Window)
 {
	 const int SCREENHEIGHT = 640;
		vector<sf::Sprite> Spritepend;
     for (b2Body* BodyIterator = World->GetBodyList(); BodyIterator != 0; BodyIterator = BodyIterator->GetNext())
        {
			
			if( BodyIterator->GetPosition().y  > SCREENHEIGHT )
			{
				if(!World->IsLocked())
				{
					World->DestroyBody(BodyIterator);
					BodyIterator = World->GetBodyList();
				}
			}
			if((int)BodyIterator->GetUserData() != 1)
			{
				if (BodyIterator->GetType() == b2_dynamicBody)
				{
					sf::Sprite ropeSprite;
					ropeSprite.setTexture(ropeTexture);
					ropeSprite.setOrigin(32.f,4.f);
					ropeSprite.setPosition(SCALE * BodyIterator->GetPosition().x, SCALE * BodyIterator->GetPosition().y);
					ropeSprite.setRotation(BodyIterator->GetAngle() * 180/b2_pi);
					Window.draw(ropeSprite);
				}


				else if(BodyIterator->GetType() == b2_staticBody )
				{
					sf::Sprite Sprite;
					Sprite.setTexture(ropeTexture);
					Sprite.setOrigin(32.f,4.f);
					Sprite.setPosition(SCALE * BodyIterator->GetPosition().x, SCALE * BodyIterator->GetPosition().y);
					Sprite.setRotation(BodyIterator->GetAngle() * 180/b2_pi);
					Window.draw(Sprite);
				}
			}
			else//if((int)BodyIterator->GetUserData() == 1)
			{
				sf::Sprite Sprite;
				Sprite.setTexture(pendTexture);
                Sprite.setOrigin(32.f,4.f);
                Sprite.setPosition(SCALE * BodyIterator->GetPosition().x, SCALE * BodyIterator->GetPosition().y);
                Sprite.setRotation(BodyIterator->GetAngle() * 180/b2_pi);
				Spritepend.push_back(Sprite);
			}
		
		
	 } 
	 for (int i = 0 ; i < Spritepend.size(); i++)
	 {
		Window.draw(Spritepend[i]);
	 }
 }


