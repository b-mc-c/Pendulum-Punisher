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
#include "Buttons.h"
#include "Level.h"
#include <iostream> 
using namespace std;
Buttons::Buttons() 
	{
		sf::RectangleShape buttonRect;
        available = true;
		clicked = false;
    }
        void Buttons::firstButton(bool avail)//setup button
        {
            available = avail;       
		}
		void Buttons::load(string name ,sf::Vector2f pos ,sf::Vector2f size)
        {		
			m_Pos = pos;
			m_Size = size;
			m_StartPos = pos;
			m_StartSize = size;
			NoOfStars = 0;

			if(!buttonTex.loadFromFile(name +"button.png"))
			{
				cout << "image did not load" << endl;
			}
			if(!starTex.loadFromFile("star.png"))
			{
				cout << "image did not load" << endl;
			}
			if(!lockTex.loadFromFile("lock.png"))
			{
				cout << "image did not load" << endl;
			}
			if(!font.loadFromFile("arial.ttf"))
			{
				cout << "font did not load" << endl;
			}
			m_name = name;
			buttonRect.setTexture(&buttonTex);//attaches texture
			buttonRect.setPosition(m_Pos);
			buttonRect.setSize(m_Size);
			lockRect.setTexture(&lockTex);//attaches texture
			lockRect.setPosition(m_Pos + sf::Vector2f ((m_Size.x * 0.5) - 25,(m_Size.y * 0.5) -25) );
			lockRect.setSize(sf::Vector2f (50,50));
			lockRect.setFillColor(sf::Color::White);
			starRect.setTexture(&starTex);
			starRect.setPosition(m_Pos - sf::Vector2f (0,50) );
			starRect.setSize(sf::Vector2f (50,50));
		
        }		
		bool Buttons::update(sf::RenderWindow& Window, float time)
        {
			sf::Vector2i mousePos;
			mousePos = sf::Mouse::getPosition(Window);
			if (available){
			sf::Vector2i mouse = sf::Mouse::getPosition();
            //clicked = false;

			if (mousePos.x >= buttonRect.getGlobalBounds().left  
				&& mousePos.x <= buttonRect.getGlobalBounds().width + buttonRect.getGlobalBounds().left 
				&& mousePos.y >= buttonRect.getGlobalBounds().top 
				&& mousePos.y <= buttonRect.getGlobalBounds().height + buttonRect.getGlobalBounds().top)
            {
				if(m_Size.x < 170)
				{
					m_Pos += sf::Vector2f(-1,-1) * 20.0f * time;
					m_Size += sf::Vector2f(2,2)  * 20.0f * time;
					buttonRect.setPosition(m_Pos);
					buttonRect.setSize(m_Size);
				}
				

				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
				clicked = true;
				return true;
				}
            }
            else
            {
				m_Pos = m_StartPos;
				m_Size = m_StartSize;
				buttonRect.setPosition(m_Pos);
				buttonRect.setSize(m_Size);
				clicked = false;
                return false;

            }

			}
			clicked = false;
            return false;

        }
		void Buttons::draw(sf::RenderWindow& Window)
        {			
			sf::Color col = sf::Color::White;
			// Create a text
			sf::Text text(m_name, font);
			text.setCharacterSize(40);
			text.setPosition(m_Pos);
			text.setStyle(sf::Text::Bold);
			text.setColor(sf::Color::Red);
			// Draw it
            if (!available)
            {			
                col =  sf::Color(35, 35, 35,255);
				
            }
            buttonRect.setFillColor(col);	
			Window.draw(buttonRect);
			for(int i = 0; i < NoOfStars ; i++)
			{
				starRect.setPosition(m_Pos - sf::Vector2f (-i * 50,50) );
				Window.draw(starRect);
			}
			 if (!available)
            {
				col =  sf::Color(255, 255, 255,75);
				lockRect.setFillColor(col);
				Window.draw(lockRect);
			
			}
			
			//Window.draw(text);
        }
		void Buttons::setAvailable( bool val)
		{
			available = val;
		}
		void Buttons::setNoOfStars(int num)
		{
			NoOfStars = num;
		}