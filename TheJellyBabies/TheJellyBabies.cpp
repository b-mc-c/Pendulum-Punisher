// TheJellyBabies.cpp : Defines the entry point for the console application.
//#include "stdafx.h"
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
#include "Entity.h"
#include "Enemy.h"
#include "BoxManager.h"
#include "EnemyManager.h"
#include "Level.h"
#include "Rope.h"
#include "Buttons.h"
#include "RopeManager.h"
//#include "SoundManager.h"
#include "gameClock.h"
using namespace std;

static const int SCREENWIDTH = 960;
static const int SCREENHEIGHT = 640;

const int SCALE = 32;
int _tmain(int argc, _TCHAR* argv[])
{
	int GameMode = 0;
	const int MENU = 0, PLAY = 1, OPTIONS = 2, HIGHSCORE = 3;
	//Level firstLevel;
	//firstLevel.LoadLevel("Level1.txt","myTextures3.png");
	Level::loadBestTimes();
	Level::LoadLevel("Level1.txt","myTextures3.png");
	/** Prepare the window */
	sf::RenderWindow Window(sf::VideoMode(SCREENWIDTH, SCREENHEIGHT, 32), "Pendulum Punisher");
	Window.setFramerateLimit(60);
	float deltatime;
	BoxManager::init();
	b2Vec2 Gravity(0.f, 9.8f);
	b2World World(Gravity);
	sf::Texture BackgroundTexture;
	sf::Texture BackgroundInstructionsTexture;
	sf::RectangleShape BackgroundImage;
	int count = 0;
	sf::Texture BoxTexture;
	sf::Texture buttonTex;
	sf::RectangleShape buttonRect;
	gameClock::clock; // starts the clock
	sf::Time timeSinceLastUpdate;
	bool jumpPressed = false;
	Entity mEntity;
	mEntity.load();
	EnemyManager::LoadFromMap("Level1_Enemies.txt");	
	Buttons buttonPlay;
	Buttons buttonHighscores;
	Buttons buttonOptions;
	Buttons buttonExit;
	Buttons PlayLevel1;
	Buttons PlayLevel2;
	Buttons PlayLevel3;
	Buttons PlayLevel4;
	Buttons PlayLevel5;
	Buttons buttonBack;
	//SoundManager soundm;
	//soundm.init();
	//soundm.loadSound();
	if(!BackgroundTexture.loadFromFile("menu.png"))
	{
		cout << "image did not load" << endl;
	}
	if(!BackgroundInstructionsTexture.loadFromFile("intsructions.png"))
	{
		cout << "image did not load" << endl;
	}
	BackgroundImage.setTexture(&BackgroundTexture);//attaches texture
	BackgroundImage.setPosition(sf::Vector2f (0,0));
	BackgroundImage.setSize(sf::Vector2f (SCREENWIDTH,SCREENHEIGHT));
	buttonPlay.load("Play", sf::Vector2f (SCREENWIDTH/2 - 64,128) ,sf::Vector2f (150,50));
	buttonHighscores.load("Scores", sf::Vector2f (SCREENWIDTH/2 - 64,256) ,sf::Vector2f (150,50));
	buttonOptions.load("Options", sf::Vector2f (SCREENWIDTH/2 - 64,384) ,sf::Vector2f (150,50));
	buttonExit.load("Exit", sf::Vector2f (SCREENWIDTH/2 - 64,512) ,sf::Vector2f (150,50));
	buttonBack.load("Back", sf::Vector2f (10,10) ,sf::Vector2f (150,50));
	PlayLevel1.load("Level1",sf::Vector2f (SCREENWIDTH/4 - 64,SCREENHEIGHT/4 - 64) ,sf::Vector2f (150,150));
	PlayLevel2.load("Level2",sf::Vector2f (SCREENWIDTH/4 *2 - 64,SCREENHEIGHT/4 - 64) ,sf::Vector2f (150,150));
	PlayLevel3.load("Level3",sf::Vector2f (SCREENWIDTH/4 * 3 - 64,SCREENHEIGHT/4 - 64) ,sf::Vector2f (150,150));
	PlayLevel4.load("Level4",sf::Vector2f (SCREENWIDTH/4  - 64,SCREENHEIGHT/2 ) ,sf::Vector2f (150,150));
	PlayLevel5.load("Level5",sf::Vector2f (SCREENWIDTH/4 * 3 - 64,SCREENHEIGHT/ 2) ,sf::Vector2f (150,150));//dec
	//buttons.buttonRect.setTexture(&buttonTex);
	RopeManager::initialise(World);
	//soundm.playSound(0);
	bool clicked = false;
	while (Window.isOpen())
    {
		timeSinceLastUpdate = gameClock::clock.getElapsedTime();
		deltatime = timeSinceLastUpdate.asSeconds();
		gameClock::clock.restart();
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			Window.close();
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::P))
		{
			//soundm.playSound(0);
		}
		switch(GameMode)
		{

		
		case MENU:
			Window.clear();
			Window.draw(BackgroundImage);
			if (buttonPlay.update(Window, deltatime))//||sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
				{	
					gameClock::clock.restart();
					//soundm.playSound(0);
					GameMode = PLAY;
					mEntity.setPosition(sf::Vector2f(29 * SCALE ,16 * SCALE));
					Level::levelNumber(0);
					break;
				}
			if (buttonExit.update(Window, deltatime))
				{
					Window.close();
					break;
					
				}
			if (buttonOptions.update(Window, deltatime))
				{
					//add code
					gameClock::clock.restart();
					PlayLevel1.setNoOfStars(Level::getStars(0));
					PlayLevel2.setNoOfStars(Level::getStars(1));
					PlayLevel3.setNoOfStars(Level::getStars(2));
					PlayLevel4.setNoOfStars(Level::getStars(3));
					PlayLevel5.setNoOfStars(Level::getStars(4));
					GameMode = OPTIONS;
					break;
				}
			if (buttonHighscores.update(Window, deltatime))
				{
					//add code
					BackgroundImage.setTexture(&BackgroundInstructionsTexture);//attaches texture
					GameMode = HIGHSCORE;
					break;
					
				}
			buttonPlay.draw(Window);
			buttonHighscores.draw(Window);
			buttonOptions.draw(Window);
			buttonExit.draw(Window);
			break;//end of menu
		case PLAY:
				
				Window.clear();
				World.Step(1/60.f, 8, 3);	
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
				{
					GameMode = MENU;
				}
				if( sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				{
					if(!jumpPressed)
					{
						jumpPressed = true;
						//soundm.playSound(1);
					}
				}
				else 
				{
					jumpPressed = false;
				}
				
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::P))
				{
					//soundm.channels[0]->setPaused(true);
				}
				
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::O))
				{
					//soundm.channels[0]->setPaused(false);
				}
				//cout << deltatime << endl;
				
				if(mEntity.Update(deltatime))
				{
					//move to next level if true
					Level::loadnextlevel(mEntity.getGameTime());
					mEntity.setPosition(sf::Vector2f(29 * SCALE ,16 * SCALE));
					PlayLevel1.setNoOfStars(Level::getStars(0));
					PlayLevel2.setNoOfStars(Level::getStars(1));
					PlayLevel3.setNoOfStars(Level::getStars(2));
					PlayLevel4.setNoOfStars(Level::getStars(3));
					PlayLevel5.setNoOfStars(Level::getStars(4));
					gameClock::clock.restart();
					GameMode = OPTIONS;
		
				}
				EnemyManager::update(deltatime);
				Level::draw(Window);
				mEntity.Draw(Window);
				EnemyManager::draw(Window);
				RopeManager::Update(Window);

			break; //end play
			case OPTIONS:
				Window.clear();
				Window.draw(BackgroundImage);
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
				{
					GameMode = MENU;
				}
				
				PlayLevel1.setAvailable(Level::islevelAvaliable(0));
				
				if (PlayLevel1.update(Window, deltatime))
				{
					//add code
					if(Level::levelNumber(0))
					{
						gameClock::clock.restart();
						//soundm.playSound(0);	
						mEntity.setPosition(sf::Vector2f(29 * SCALE ,16 * SCALE));
						GameMode = PLAY;
					}
				}
				PlayLevel2.setAvailable(Level::islevelAvaliable(1));
				if (PlayLevel2.update(Window, deltatime))
				{
					//add code
					if(Level::levelNumber(1))
					{
						gameClock::clock.restart();
						//soundm.playSound(0);
						mEntity.setPosition(sf::Vector2f(29 * SCALE ,16 * SCALE));
						GameMode = PLAY;
					}
				}
				PlayLevel3.setAvailable(Level::islevelAvaliable(2));
				if (PlayLevel3.update(Window, deltatime))
				{
					//add code
					if(Level::levelNumber(2))
					{
						gameClock::clock.restart();
						//soundm.playSound(0);
						mEntity.setPosition(sf::Vector2f(29 * SCALE ,16 * SCALE));
						GameMode = PLAY;
					}
				}
				PlayLevel4.setAvailable(Level::islevelAvaliable(3));
				if (PlayLevel4.update(Window, deltatime))
				{
					//add code
					if(Level::levelNumber(3))
					{
						gameClock::clock.restart();
						//soundm.playSound(0);
						mEntity.setPosition(sf::Vector2f(29 * SCALE ,16 * SCALE));
						GameMode = PLAY;
					}
				}
				PlayLevel5.setAvailable(Level::islevelAvaliable(4));
				if (PlayLevel5.update(Window, deltatime))
				{
					//add code
					if(Level::levelNumber(4))
					{
						gameClock::clock.restart();
						//soundm.playSound(0);
						mEntity.setPosition(sf::Vector2f(29 * SCALE ,16 * SCALE));
						GameMode = PLAY;
					}
				}
				if (buttonBack.update(Window, deltatime))
				{
					GameMode = MENU;
				}
				buttonBack.draw(Window);
				PlayLevel1.draw(Window);
				PlayLevel2.draw(Window);
				PlayLevel3.draw(Window);
				PlayLevel4.draw(Window);
				PlayLevel5.draw(Window);
			break;//end of OPTIONS
			case HIGHSCORE:
				Window.clear();
				Window.draw(BackgroundImage);
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
				{
					BackgroundImage.setTexture(&BackgroundTexture);
					GameMode = MENU;
				}
				if (buttonBack.update(Window, deltatime))
				{
					BackgroundImage.setTexture(&BackgroundTexture);
					GameMode = MENU;
				}
				buttonBack.draw(Window);
			break;//end of HIGHSCORES
		}
		Window.display();
		}
		
        
    
	return 0;
}

















