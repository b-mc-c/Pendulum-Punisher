#ifndef BUTTONS_H
#define BUTTONS_H
#include "stdafx.h"
#include "BoundingBox.h"

#include <vector>;
#include <iostream> 

using namespace std;

class Buttons
{
public:
	Buttons();
	void firstButton(bool avail);
	void load(string name,sf::Vector2f pos ,sf::Vector2f size);
	bool Buttons::update(sf::RenderWindow& Window, float time);
	void draw(sf::RenderWindow& Window);
	sf::RectangleShape buttonRect;
	void setAvailable(bool val);
	void setNoOfStars(int num);
	
private:	
	sf::Vector2f m_Pos;
	sf::Vector2f m_Size;
	sf::Texture buttonTex;
	sf::Texture lockTex;
	sf::RectangleShape lockRect;
	sf::Sprite image;
	sf::Texture starTex;
	sf::RectangleShape starRect;
	string m_name;
    bool clicked;
    bool available;
	sf::Font font;
	sf::Vector2f m_StartPos;
	sf::Vector2f m_StartSize;
	int NoOfStars;
	

	
};
#endif