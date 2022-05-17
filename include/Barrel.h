#include "Object.h"

#pragma once
using namespace std;

class Barrel : public Object {
private:
	bool isVisible;								//Private attribute that determines whether barrel is visible
public:
	void init(sf::RenderWindow *window, string texturePath, Coord Pos);			//initilization of barrel class, this function must be defined because it is pure virtual
	Coord getPosition();						//Returns barrel position
	bool getVisible(void);						//Returns isVisible attribute of barrel
	void setVisible(bool visible);				//Hides or shows the barrel (changes its visible attribute)
	~Barrel();									//destructor of barrel to deallocate memory

};

