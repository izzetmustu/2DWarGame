#include "Barrel.h"

void Barrel::init(sf::RenderWindow *window, string texturePath, Coord Pos) {
	this->window = window;				//pointer assignment
	texture = new sf::Texture;
	texture->loadFromFile(texturePath+"barrel.png");		//load texture
	sprite.setTexture(*texture);		//set sprites texture from loaded texture
	this->pos = Pos;					//assign object position to passed position
	sprite.setPosition(pos.x, pos.y);	//spawn sprite to passed position
	isVisible = true;
}

//getter function
Coord Barrel::getPosition() {
	return pos;
}

//getter function
bool Barrel::getVisible(void) {
	return isVisible;
}

//setter function
void Barrel::setVisible(bool visible) {
	isVisible = visible;
}

//destructor of barrel to deallocate memory
Barrel::~Barrel() {
	delete texture;
}