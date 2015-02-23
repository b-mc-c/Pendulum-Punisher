#ifndef ROPE_H
#define ROPE_H

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
#include <iostream> 
#include <Box2D.h>
#include <Box2D\Dynamics\b2Body.h>
#include "stdafx.h"

class Rope
{
public:
	Rope();
	void addRope(b2World& m_world, sf::Vector2f playerPos);
	void initialiseRope(b2World& m_world, int anchorX, int anchorY, int SCALE);
	void TwoRopes(b2World& m_world, int anchor1x, int anchor1y, int acnhor2x, int anchor2y,int noOfLinks1, int noOfLinks2, int SCALE);
	void Update();
	void Draw(sf::RenderWindow& window);
	void setPosition();
	void cutRope( );
	sf::Vector2f getPosition();
	b2BodyDef anchorBodyDef;
	b2BodyDef anchorBodyDef2;
	b2BodyDef ropeBodyDef;
	b2BodyDef ropeBodyDef2;
	b2BodyDef pendulumDef;
	//player rope and anchor def
    b2BodyDef playerRopeBodyDef;
    b2BodyDef playerAnchorBodyDef;
	
protected:
	//const int PPM;
    //b2BodyDef bodyDef;
    //b2PolygonDef boxDef;
    //b2CircleDef circleDef;
	//b2RopeJoint rope;
    b2RevoluteJointDef revolute_joint;
	b2RevoluteJointDef revoluteJointDef1;
    b2Body* anchorlink;
	b2Body* anchorlink2;
	b2Body* link;
	b2Body* link2;
	b2Body* pendulum;
	b2PolygonShape linkShape;
	b2PolygonShape pendulumShape;
	b2FixtureDef fixtureDef;
	b2FixtureDef pendFixDef;
	
	//player created rope variables
    b2RevoluteJointDef playerRevoluteJointDef;  
    b2Body* playerAnchorlink;
    b2Body* playerLink;

	sf::Sprite ed;
};

#endif
