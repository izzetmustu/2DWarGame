#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Coord.h"
#include <string.h>
#include <iostream>

using namespace std;

#pragma once
class Object {					//Abstract class
protected:
	sf::RenderWindow* window;	//OSFML window object
	sf::Texture* texture;		//Object texture
	sf::Sprite sprite;			//Object sprite
	Coord pos;					//Object position
public:
	virtual void init(sf::RenderWindow *window, string texturePath, Coord Pos) = 0;		//Pure virtual function	makes the class abstract so that we can't create instances of this class										
	void paint();																		//Draws the barrel sprite
	virtual ~Object() = 0;																//Pure virtual destructor
};

