#include "Bullet.h"

void Bullet::init(sf::RenderWindow *window, string texturePath, Coord Pos, int state) {
	this->window = window;				//pointer assignment
	texture = new sf::Texture;
	texture->loadFromFile(texturePath + "bullet.png");		//load texture
	sprite.setTexture(*texture);		//set sprites texture from loaded texture
	setSpeed(0);

	//soldier can shoot standing up, down, right, left or walking any direction
	if (state == 0 || state == 7 || state == 8) {
		angle = 0;
		pos = Coord(Pos.x + 60, Pos.y - 10);
		sprite.setPosition(pos.x, pos.y);
		sprite.setRotation(angle);
	} 
	else if (state == 2 || state == 9 || state == 10) {
		angle = 90;
		pos = Coord(Pos.x + 120, Pos.y + 75);
		sprite.setPosition(pos.x, pos.y);
		sprite.setRotation(angle);
	}
	else if (state == 3 || state == 4 || state == 11) {
		angle = 180;
		pos = Coord(Pos.x + 30, Pos.y + 125);
		sprite.setPosition(pos.x, pos.y);
		sprite.setRotation(angle);
	} 
	else if (state == 6 || state == 12 || state == 13) {
		angle = 270;
		pos = Coord(Pos.x - 25, Pos.y + 40);
		sprite.setPosition(pos.x, pos.y);
		sprite.setRotation(angle);
	}
}

//Moves the bullet in its travel direction(angle)
void Bullet::move(void) {						
	if (angle == 0) {
		pos.y -= speed;
		sprite.setPosition(pos.x, pos.y);
	}
	else if (angle == 90) {
		pos.x += speed;
		sprite.setPosition(pos.x, pos.y);
	}
	else if (angle == 180) {
		pos.y += speed;
		sprite.setPosition(pos.x, pos.y);
	}
	else if (angle == 270) {
		pos.x -= speed;
		sprite.setPosition(pos.x, pos.y);
	}
}

//Sets the bullet speed
void Bullet::setSpeed(float speed) {			
	this->speed = speed;
}

//destructor of bullet to deallocate memory
Bullet::~Bullet() {
	delete texture;
}