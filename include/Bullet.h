#include "Object.h"

using namespace std;

#pragma once
class Bullet : public Object{
private:
	friend class BulletList;			//added to access the next pointer in the linkedlist
	float speed;						//Bullet speed (you can pick any speed unit you wish)
	int angle;							//Bullet travel angle
	Bullet* next;						//Pointer to next bullet in a linked list
public:
	void init(sf::RenderWindow *window, string texturePath, Coord Pos) {}			//this function must be defined because it is pure virtual
	void init(sf::RenderWindow *window, string texturePath, Coord Pos, int state);	//overloaded function
	void move(void);					//Moves the bullet in its travel direction(angle)
	void setSpeed(float speed);			//Sets the bullet speed
	~Bullet();							//destructor of bullet to deallocate memory		
};

