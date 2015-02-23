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

using namespace std;
#include "Level.h"
#include "gameClock.h"


std::vector<sf::Sprite> Level::background(0); 
std::vector<int> Level::bestTimes(0);
const int Level::SCALE = 32;
const int Level::MAXLEVELS = 5;
int Level::currentlevel = 0;
sf::Texture Level::texture; 


Level::Level()
{
	currentlevel = 0;
}	
void  Level::reloadlevel()
{
	BoxManager::clearAll();
	RopeManager::RemoveRopes();
	string levelnames[] = {"Level1.txt","Level2.txt","Level3.txt","Level4.txt","Level5.txt"};
	string leveltexturenames[] = {"myTextures3.png","myTextures4.png","myTextures5.png","myTextures5.png","myTextures7.png"};
	string enemylevelnames[] = {"Level1_Enemies.txt","Level2_Enemies.txt","Level3_Enemies.txt","Level4_Enemies.txt","Level5_Enemies.txt"};
	LoadLevel(levelnames[currentlevel],leveltexturenames[currentlevel]);
	EnemyManager::LoadFromMap(enemylevelnames[currentlevel]);
	RopeManager::addRope(currentlevel);
	gameClock::clock.restart();
}
void Level::loadnextlevel(float lastGameTime )
{
	
	
	int stars = 1;
	if (currentlevel == 0)
	{
		if (lastGameTime <= 14)
		{
			stars = 3;
		}
		else if (lastGameTime <= 20)
		{
			stars = 2;
		}
	}
	if (currentlevel == 1)
	{
		if (lastGameTime <= 25)
		{
			stars = 3;
		}
		else if (lastGameTime <= 32)
		{
			stars = 2;
		}
	}
	if (currentlevel == 2)
	{
		if (lastGameTime <= 26)
		{
			stars = 3;
		}
		else if (lastGameTime <= 32)
		{
			stars = 2;
		}
	}
	if (currentlevel == 2)//strange
	{
		if (lastGameTime <= 26)
		{
			stars = 3;
		}
		else if (lastGameTime <= 32)
		{
			stars = 2;
		}
	}
	if (currentlevel == 3)
	{
		if (lastGameTime <= 25)
		{
			stars = 3;
		}
		else if (lastGameTime <= 32)
		{
			stars = 2;
		}
	}
	if (currentlevel == 4)
	{
		if (lastGameTime <= 40)
		{
			stars = 3;
		}
		else if (lastGameTime <= 52)
		{
			stars = 2;
		}
	}
	if(bestTimes[currentlevel] < stars)
	{
		bestTimes[currentlevel] = stars;
	}
	saveBestTimes();
	currentlevel++;
	if (currentlevel >= MAXLEVELS)
	{
		currentlevel = 0;
	}
		
}
// a load level method inside 
void Level::LoadLevel(string name, string texturename)
{
	background.clear();
	BoxManager::clearAll();
	vector<string> map =Level::loadALevelFromTextFile(name);
	const int mapX = 30;
	const int mapY = 20;
	sf::Sprite temp;
	
		if(!texture.loadFromFile(texturename))//"myTextures3.png"
		{
			cout << "image did not load" << endl;
		}

		int noOfSpritesOnX = 10;
		if("Level5.txt" == name)
		{
			noOfSpritesOnX = 10;
		}
		const int noOfSpritesOnY = 1;
		sf::Vector2u size = texture.getSize();
		float xscale  = SCALE / (float)size.x;
		float yscale = SCALE / (float)size.y;
		temp.setScale(sf::Vector2f(xscale * noOfSpritesOnX,yscale * noOfSpritesOnY));
		temp.setTexture(texture);
		for (int y = 0; y < mapY; y++)
		{
			for (int x = 0; x < mapX; x++)
			{
				char c = (char)map[y][x];
				temp.setPosition((sf::Vector2f(x * SCALE,y * SCALE)));
		
				if (c == 'D')
				{	
					BoxManager::addDoor(x * SCALE,y*SCALE,SCALE,SCALE);
					temp.setTextureRect(sf::IntRect(7 * SCALE, 0 , SCALE, SCALE));
			
				}
				if (c == 'w')
				{	
					temp.setTextureRect(sf::IntRect(0 * SCALE, 0 , SCALE, SCALE));
			
				}
				if (c == 'h')
				{	
					temp.setTextureRect(sf::IntRect(1 * SCALE, 0 , SCALE, SCALE));
			
				}
				if (c == 'L')
				{	
					
					temp.setTextureRect(sf::IntRect(3 * SCALE, 0 , SCALE, SCALE));	
					BoxManager::addLadder(x * SCALE,y*SCALE,SCALE,SCALE);
				}
				if (c == 'F')
				{	
		
					temp.setTextureRect(sf::IntRect(2 * SCALE, 0, SCALE, SCALE));	
					BoxManager::addFloor(x * SCALE,y*SCALE,SCALE,SCALE);
				}
				if (c == 'C')
				{	
		
					temp.setTextureRect(sf::IntRect(4 * SCALE, 0, SCALE, SCALE));	
					BoxManager::addChest(x * SCALE,y*SCALE,SCALE,SCALE);
				}
				if (c == 'H')
				{	
		
					temp.setTextureRect(sf::IntRect(5 * SCALE, 0, SCALE, SCALE));	
					BoxManager::addChest(x * SCALE,y*SCALE,SCALE,SCALE);
				}
				if (c == 't')
				{	
					temp.setTextureRect(sf::IntRect(6 * SCALE, 0 , SCALE, SCALE));
			
				}
				if (c == 'X')
				{	
					temp.setTextureRect(sf::IntRect(8 * SCALE, 0 , SCALE, SCALE));
					BoxManager::addFloor(x * SCALE,y*SCALE,SCALE,SCALE);
				}
				if (c == 'P')
				{	
					temp.setTextureRect(sf::IntRect(6 * SCALE, 0 , SCALE, SCALE));
					BoxManager::addFloor(x * SCALE,y*SCALE,SCALE,SCALE);
				}
					if (c == 'Y')
				{	
					temp.setTextureRect(sf::IntRect(2 * SCALE, 0 , SCALE, SCALE));
				}
					if (c == 'A')
				{	
					temp.setTextureRect(sf::IntRect(9 * SCALE, 0 , SCALE, SCALE));
					BoxManager::addHook(x * SCALE,y*SCALE,SCALE,SCALE);
				}
				background.push_back(temp);
        
			}
		}
	}
bool  Level::levelNumber(int i)
{
	if(i == 0)
	{
		currentlevel = i;
		reloadlevel();
		return true;
	}
	else if(bestTimes[i-1] != 0)
	{
		currentlevel = i;
		reloadlevel();
		return true;
	}
	return false;
	
}
void Level::loadBestTimes()
{
	ifstream myfile;
	myfile.open("scores.txt");	
	int c;
	while ( myfile >> c ) 
	{
		bestTimes.push_back(c);
	}

	myfile.close();
}
void Level::saveBestTimes()
{
	ofstream myfile;
	myfile.open("scores.txt");
	for(int i = 0 ; i < bestTimes.size(); i++)
	{
		myfile << bestTimes[i] << "\n";
	}
    
   
    myfile.close();
  
}
//inside the main while loop
//in a cpp file  put this inside a draw method that takes (sf::RenderWindow& Window)  as its arguements
bool  Level::islevelAvaliable(int i)
{
	if (i == 0 )
	{
		return true;
	}
	else if (bestTimes[i- 1] > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
void Level::draw(sf::RenderWindow& Window) 
{
        for(int i = 0 ; i < background.size(); i++)
		{
			Window.draw(background[i]);
		}
 
        
 
    
}
vector<string> Level::loadALevelFromTextFile(string name)
{
	vector<string > mystringvector;
	ifstream myfile;
	myfile.open(name);	
	string c = "";
	while ( myfile >> c ) 
	{
		mystringvector.push_back(c);
	}

	myfile.close();
	return mystringvector;
}
int Level::getStars(int levelNum)
{
	return bestTimes[levelNum];
}