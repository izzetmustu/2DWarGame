#include "Object.h"

#pragma once
using namespace std;

class Sandbag : public Object {
public:
	void init(sf::RenderWindow *window, string texturePath, Coord Pos);		//initilization of sandbag class, this function must be defined because it is pure virtual
	Coord getPosition();													//Returns sandbag position
	~Sandbag();																//destructor of sandbag to deallocate memory
};

