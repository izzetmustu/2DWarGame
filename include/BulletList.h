#include "Bullet.h"
#include "Player.h"

using namespace std;

#pragma once
class BulletList {
private:
	Bullet* list;							//Pointer to a linked list of bullets
	sf::RenderWindow* window;				//SFML window object
	string path;							//Texture path
	int counter;							//Bullet counter, it is added to check bullet counts, not necessary
public:
	BulletList(sf::RenderWindow* window, string texturepath);	//Constructor for the BulletList
	void add(Coord pos, int state, float s);					//Adds a new bullet to the list, s parameter is added for speed
	void update(void);											//Draws every bullet in the list and then moves them
	void checkCollision(Player* players, Barrel* barrels, Sandbag* sandbags, int np, int nb, int ns);		//Checks whether a bullet in the list collided with other objects or with the edge of the screen
	void deleteBullet(Bullet* deleted);							//Delete the bullet that that collided
	void deleteList();											//Delete entire linked list
};

