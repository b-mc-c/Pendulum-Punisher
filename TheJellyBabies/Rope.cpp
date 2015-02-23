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
#include <iostream> 
#include "Rope.h"

Rope::Rope()
{

}

void Rope::TwoRopes(b2World& m_world, int anchor1x, int anchor1y, int anchor2x, int anchor2y,int noOfLinks1, int noOfLinks2, int SCALE)
{
	anchorBodyDef.type = b2_staticBody;
	anchorBodyDef.position.Set(anchor1x/SCALE, anchor1y/SCALE);
	fixtureDef.density = 1;
	linkShape.SetAsBox(8.f/SCALE,8.f/SCALE);
	fixtureDef.shape = &linkShape;

	ropeBodyDef.type = b2_dynamicBody;
	ropeBodyDef.position.Set(anchor1x/SCALE, anchor1y/SCALE);

	//Where chain will be connected from 
	anchorlink = m_world.CreateBody( &anchorBodyDef);
	anchorlink->CreateFixture( &fixtureDef );
	
	//first joint in chain
	link = m_world.CreateBody( &ropeBodyDef);
	link->CreateFixture( &fixtureDef );

	revolute_joint.localAnchorA.Set(-.25,0);
	revolute_joint.localAnchorB.Set(.25,0);
	revolute_joint.bodyA = anchorlink;
	revolute_joint.bodyB = link;
	m_world.CreateJoint( &revolute_joint );

	//use same definitions to create multiple bodies
	//first chain/rope
	for (int i = 0; i < noOfLinks1; i++) 
	{
		ropeBodyDef.position.Set(anchor1x/SCALE, anchor1y/SCALE + 2);

		b2Body* newLink( m_world.CreateBody(&ropeBodyDef));
		newLink->CreateFixture( &fixtureDef );
		newLink->SetAngularDamping(0.2f);
		newLink->SetLinearDamping(0.2f);
		//...joint creation will go here...
		//set up the common properties of the joint before entering the loop
		b2RevoluteJointDef revoluteJointDef;
		revoluteJointDef.localAnchorA.Set(-.25,0);
		revoluteJointDef.localAnchorB.Set(.25,0);
		//inside the loop, only need to change the bodies to be joined
		revoluteJointDef.bodyA = link;
		revoluteJointDef.bodyB = newLink;
		m_world.CreateJoint( &revoluteJointDef );


		link = newLink;
	}
//*************************************************************************************************
	//2nd Chain

	anchorBodyDef2.type = b2_staticBody;
	anchorBodyDef2.position.Set(anchor2x/SCALE, anchor2y/SCALE);

	//Where chain will be connected from 
	anchorlink2 = m_world.CreateBody( &anchorBodyDef2);
	anchorlink2->CreateFixture( &fixtureDef );

	ropeBodyDef2.type = b2_dynamicBody;
	ropeBodyDef2.position.Set(anchor2x/SCALE, anchor2y/SCALE);

	//first joint in chain in second chain
	link2 = m_world.CreateBody( &ropeBodyDef2);
	link2->CreateFixture( &fixtureDef );

	revolute_joint.localAnchorA.Set(-.25,0);
	revolute_joint.localAnchorB.Set(.25,0);
	revolute_joint.bodyA = anchorlink2;
	revolute_joint.bodyB = link2;
	m_world.CreateJoint( &revolute_joint );

	//use same definitions to create multiple bodies
	//second Chain/Rope
	for (int i = 0; i < noOfLinks2; i++) 
	{
		ropeBodyDef2.position.Set(anchor2x/SCALE, anchor2y/SCALE+6);
		b2Body* newLink2( m_world.CreateBody(&ropeBodyDef2));
		newLink2->CreateFixture( &fixtureDef );
		newLink2->SetAngularDamping(0.2f);
		newLink2->SetLinearDamping(0.2f);
		//...joint creation will go here...
		//set up the common properties of the joint before entering the loop
		b2RevoluteJointDef revoluteJointDef2;
		revoluteJointDef2.localAnchorA.Set(-.25,0);
		revoluteJointDef2.localAnchorB.Set(.25,0);
		//inside the loop, only need to change the bodies to be joined
		revoluteJointDef2.bodyA = link2;
		revoluteJointDef2.bodyB = newLink2;
		m_world.CreateJoint( &revoluteJointDef2 );


		link2 = newLink2;
	}

	
	//Pendulum bodyDef
	pendulumDef.type = b2_dynamicBody;
	
	pendulumDef.position.Set(anchor1x/SCALE, anchor1y/SCALE + 1);
	pendFixDef.density = 1;
	pendulumShape.SetAsBox(16.f/SCALE,16.f/SCALE);
	pendFixDef.shape = &pendulumShape;
	pendulum = m_world.CreateBody(&pendulumDef);
	pendulum->SetUserData((void*)1);
	//pendulum->SetUserData((void*)"pend");

	//connect to rope 1
	b2RevoluteJointDef pendReveJointDef;
	pendReveJointDef.localAnchorA.Set(-.25,0);
	pendReveJointDef.localAnchorB.Set(.25,0);
	pendReveJointDef.bodyA = link;
	pendReveJointDef.bodyB = pendulum;
	m_world.CreateJoint( &pendReveJointDef );

	//connect to rope 2
	b2RevoluteJointDef pendReveJointDef1;
	pendReveJointDef1.localAnchorA.Set(-.25,0);
	pendReveJointDef1.localAnchorB.Set(.25,0);
	pendReveJointDef1.bodyA = link2;
	pendReveJointDef1.bodyB = pendulum;
	m_world.CreateJoint( &pendReveJointDef1 );


//	ed.
}
void Rope::addRope(b2World& m_world, sf::Vector2f playerPos)
{
        int distanceToPend = 0;
        int noOfLinks = 0;
 
 
        distanceToPend = sqrt((playerPos.x- (pendulum->GetPosition().x * 32)) *(playerPos.x - (pendulum->GetPosition().x * 32)) +
                (playerPos.y- (pendulum->GetPosition().y * 32)) *(playerPos.y - (pendulum->GetPosition().y *32) ));// Math.sqrt((x2*x2)-(x1*x1) + (y2*y2)-(y1*y1);
 
        noOfLinks = distanceToPend/(16);
 
        playerAnchorBodyDef.type = b2_staticBody;
        playerAnchorBodyDef.position.Set(playerPos.x/32, playerPos.y/32);
        fixtureDef.density = 1;
        linkShape.SetAsBox(8.f/32,8.f/32);
        fixtureDef.shape = &linkShape;
 
        playerRopeBodyDef.type = b2_dynamicBody;
        playerRopeBodyDef.position.Set(playerPos.x/32, playerPos.y/32);
 
        //Where chain will be anchored from
        playerAnchorlink = m_world.CreateBody( &playerAnchorBodyDef);
        playerAnchorlink->CreateFixture( &fixtureDef );
       
        //first joint in chain
        playerLink = m_world.CreateBody( &playerRopeBodyDef);
        playerLink->CreateFixture( &fixtureDef );
 
        playerRevoluteJointDef.localAnchorA.Set(-.25,0);
        playerRevoluteJointDef.localAnchorB.Set(.25,0);
        playerRevoluteJointDef.bodyA = playerAnchorlink;
        playerRevoluteJointDef.bodyB = playerLink;
        m_world.CreateJoint( &playerRevoluteJointDef );
 
        //use same definitions to create multiple bodies
        //first chain/rope
        for (int i = 0; i < noOfLinks; i++)
        {
                ropeBodyDef.position.Set(playerPos.x/32, playerPos.y/32 + 2);
 
                b2Body* newLink( m_world.CreateBody(&playerRopeBodyDef));
                newLink->CreateFixture( &fixtureDef );
                newLink->SetAngularDamping(0.2f);
                newLink->SetLinearDamping(0.2f);
                //...joint creation will go here...
                //set up the common properties of the joint before entering the loop
                b2RevoluteJointDef revoluteJointDef;
                revoluteJointDef.localAnchorA.Set(-.25,0);
                revoluteJointDef.localAnchorB.Set(.25,0);
                //inside the loop, only need to change the bodies to be joined
                revoluteJointDef.bodyA = playerLink;
                revoluteJointDef.bodyB = newLink;
                m_world.CreateJoint( &revoluteJointDef );
 
 
                playerLink = newLink;
        }
 
 
 
 
        //connect to rope 2
        b2RevoluteJointDef pendReveJointDef1;
        pendReveJointDef1.localAnchorA.Set(-.25,0);
        pendReveJointDef1.localAnchorB.Set(.25,0);
        pendReveJointDef1.bodyA = playerLink;
        pendReveJointDef1.bodyB = pendulum;
        m_world.CreateJoint( &pendReveJointDef1 );
 
}

void Rope::cutRope()
{

	anchorlink->SetType(b2_dynamicBody);

}

