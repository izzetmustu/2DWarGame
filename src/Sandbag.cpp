#include "Sandbag.h"

void Sandbag::init(sf::RenderWindow *window, string texturePath, Coord Pos) {
	this->window = window;				//pointer assignment
	texture = new sf::Texture;
	texture->loadFromFile(texturePath + "bags.png");		//load texture
	sprite.setTexture(*texture);		//set sprites texture from loaded texture
	this->pos = Pos;					//assign object position to passed position
	sprite.setPosition(pos.x, pos.y);	//spawn sprite to passed position
}

//getter function
Coord Sandbag::getPosition() {
	return pos;
}

//destructor of sandbag to deallocate memory
Sandbag::~Sandbag() {
	delete texture;
}
