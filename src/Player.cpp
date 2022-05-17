#include "Player.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

void Player::init(sf::RenderWindow *window, string textBasePatch, Coord pos) {
	this->window = window;					//pointer assignment
	texture = new sf::Texture[14];			//load all the textures
	for (int i = 0; i < 14; i++) {
		texture[i].loadFromFile(textBasePatch + "soldier" + to_string(i) + ".png");
	}
	sprite.setTexture(texture[0]);			//default texture
	setPosition(pos);						//starting position
	state = 0;								//default state
	s = 0;									//default state2
	score = 0;								//default score
	speed = 0;								//default speed
	//default walking direction states and shooting state
	uppressed = false;
	downpressed = false;
	rightpressed = false;
	leftpressed = false;
	shoot = false;
}

//update position of the instance
void Player::setPosition(Coord pos) {
	this->pos = pos;
	sprite.setPosition(pos.x, pos.y);
}

//if the next position is of player inside the other objects, don't take action
bool Player::checkCollision(Barrel *barrels, Sandbag *sandbags, int nb, int ns, Coord next_pos) {
	//numbers are acquired by looking at the textures from paint, because there are gaps in the textures
	/*
	____________
	|		    |
	|		    |
	|		    |		object
	|		    |
	|_______N___|		N: any boundary of the next player pos
		  -----
		  |	  |
		  |	  |			player
	      |   |
		  -----

	*/
	//Barrels collision detection
	for (int i = 0; i < nb; i++) {
		if (barrels[i].getVisible() && (next_pos.x + sprite.getGlobalBounds().width/2 >= barrels[i].getPosition().x) && (next_pos.x + sprite.getGlobalBounds().width / 2 <= barrels[i].getPosition().x + 70) && (next_pos.y + sprite.getGlobalBounds().height / 2 >= barrels[i].getPosition().y) && (next_pos.y + sprite.getGlobalBounds().height / 2 <= barrels[i].getPosition().y + 60)) {
			return true;
		}
	}
	//Sandbag collision detection
	for (int i = 0; i < ns; i++) {
		if ((next_pos.x + sprite.getGlobalBounds().width / 2 >= sandbags[i].getPosition().x) && (next_pos.x + sprite.getGlobalBounds().width / 2 <= sandbags[i].getPosition().x + 60) && (next_pos.y + sprite.getGlobalBounds().height / 2 >= sandbags[i].getPosition().y) && (next_pos.y + sprite.getGlobalBounds().height / 2 <= sandbags[i].getPosition().y + 70)) {
			return true;
		}
	}
	//Window boundaries
	if (next_pos.x <0 || next_pos.x+ sprite.getGlobalBounds().width > window->getSize().x || next_pos.y < 0 || next_pos.y+ sprite.getGlobalBounds().height > window->getSize().y) {
		return true;
	}
	return false;
}

//state diagram is applied
void Player::walk(WalkDirection dir, Barrel *barrels, Sandbag *sandbags, int nb, int ns) {
	switch (this->state) {
		case 0:
			switch (dir) {
				case Left:
					s = 1;
					state = 7;
					sprite.setTexture(texture[state]);
					break;
				case Up:
					if (s == 1) {	
						Coord next(pos.x, -speed + pos.y);	//check if the next position is of player inside the other objects, don't take action
						if (!checkCollision(barrels, sandbags, nb, ns, next)) {
							s = 0;
							state = 8;
							sprite.setTexture(texture[state]);
							setPosition(next);
						}
					}
					else {
						Coord next(pos.x, -speed + pos.y);
						if (!checkCollision(barrels, sandbags, nb, ns, next)) {
							s = 1;
							state = 7;
							sprite.setTexture(texture[state]);
							setPosition(next);
						}
					}
					break;
				case Right:
					this->state = 1;
					this->sprite.setTexture(texture[state]);
					break;
				case Down:
					break;
				default:
					break;
			}
			break;
		case 1:
			switch (dir) {
				case Left:
					state = 0;
					sprite.setTexture(texture[state]);
					break;
				case Up:
					state = 0;
					sprite.setTexture(texture[state]);
					break;
				case Right:
					state = 2;
					sprite.setTexture(texture[state]);
					break;
				case Down:
					state = 2;
					sprite.setTexture(texture[state]);
					break;
				default:
					break;
			}
			break;
		case 2:
			switch (dir) {
				case Left:
					break;
				case Up:
					state = 1;
					sprite.setTexture(texture[state]);
					break;
				case Right:
					if (s == 1) {
						Coord next(speed + pos.x, pos.y);
						if (!checkCollision(barrels, sandbags, nb, ns, next)) {
							s = 0;
							state = 9;
							sprite.setTexture(texture[state]);
							setPosition(next);
						}
					}
					else {
						Coord next(speed + pos.x, pos.y);
						if (!checkCollision(barrels, sandbags, nb, ns, next)) {
							s = 1;
							state = 10;
							sprite.setTexture(texture[state]);
							setPosition(next);
						}
					}
					break;
				case Down:
					s = 1;
					state = 3;
					sprite.setTexture(texture[state]);
					break;
				default:
					break;
			}
			break;
		case 3:
			switch (dir) {
				case Left:
					state = 4;
					sprite.setTexture(texture[state]);
					break;
				case Up:
					break;
				case Right:
					state = 2;
					sprite.setTexture(texture[state]);
					break;
				case Down:
				{
					Coord next(pos.x, speed + pos.y);
					if (!checkCollision(barrels, sandbags, nb, ns, next)) {
						state = 4;
						sprite.setTexture(texture[state]);
						setPosition(next);
					}
				}
					break;
				default:
					break;
			}
			break;
		case 4:
			switch (dir) {
				case Left:
					state = 5;
					sprite.setTexture(texture[state]);
					break;
				case Up:
					break;
				case Right:
					s = 0;
					state = 3;
					sprite.setTexture(texture[state]);
					break;
				case Down:
					if (s == 1) {
						Coord next(pos.x, speed + pos.y);
						if (!checkCollision(barrels, sandbags, nb, ns, next)) {
							s = 0;
							state = 11;
							sprite.setTexture(texture[state]);
							setPosition(next);
						}
					}
					else {
						Coord next(pos.x, speed + pos.y);
						if (!checkCollision(barrels, sandbags, nb, ns, next)) {
							s = 1;
							state = 3;
							sprite.setTexture(texture[state]);
							setPosition(next);
						}
					}
					break;
				default:
					break;
			}
			break;
		case 5:
			switch (dir) {
				case Left:
					state = 6;
					sprite.setTexture(texture[state]);
					break;
				case Up:
					state = 6;
					sprite.setTexture(texture[state]);
					break;
				case Right:
					state = 4;
					sprite.setTexture(texture[state]);
					break;
				case Down:
					state = 4;
					sprite.setTexture(texture[state]);
					break;
				default:
					break;
			}
			break;
		case 6:
			switch (dir) {
				case Up:
					s = 1;
					state = 7;
					sprite.setTexture(texture[state]);
					break;
				case Left:
					if (s == 1) {
						Coord next(-speed + pos.x, pos.y);
						if (!checkCollision(barrels, sandbags, nb, ns, next)) {
							s = 0;
							state = 12;
							sprite.setTexture(texture[state]);
							setPosition(next);
						}
					}
					else {
						Coord next(-speed + pos.x, pos.y);
						if (!checkCollision(barrels, sandbags, nb, ns, next)) {
							s = 1;
							state = 13;
							sprite.setTexture(texture[state]);
							setPosition(next);
						}
					}
					break;
				case Right:
					break;
				case Down:
					state = 5;
					sprite.setTexture(texture[state]);
					break;
				default:
					break;
			}
			break;
		case 7:
			switch (dir) {
				case Left:
					state = 6;
					sprite.setTexture(texture[state]);
					break;
				case Up:
				{
					Coord next(pos.x, -speed + pos.y);
					if (!checkCollision(barrels, sandbags, nb, ns, next)) {
						state = 0;
						sprite.setTexture(texture[state]);
						setPosition(next);
					}
				}
					break;
				case Right:
					state = 0;
					sprite.setTexture(texture[state]);
					break;
				case Down:
					state = 6;
					sprite.setTexture(texture[state]);
					break;
				default:
					break;
			}
			break;
		case 8:					
			switch (dir) {
				case Left:
					state = 0;
					sprite.setTexture(texture[state]);
					break;
				case Up:
				{
					Coord next(pos.x, -speed + pos.y);
					if (!checkCollision(barrels, sandbags, nb, ns, next)) {
						state = 0;
						sprite.setTexture(texture[state]);
						setPosition(next);
					}
				}
					break;
				case Right:
					state = 0;
					sprite.setTexture(texture[state]);
					break;
				case Down:
					state = 0;
					sprite.setTexture(texture[state]);
					break;
				default:
					break;
			}
			break;
		case 9:
			switch (dir) {
				case Left:
					state = 2;
					sprite.setTexture(texture[state]);
					break;
				case Up:
					state = 2;
					sprite.setTexture(texture[state]);
					break;
				case Right:
				{
					Coord next(speed + pos.x, pos.y);
					if (!checkCollision(barrels, sandbags, nb, ns, next)) {
						state = 2;
						sprite.setTexture(texture[state]);
						setPosition(next);
					}
				}
					break;
				case Down:
					state = 2;
					sprite.setTexture(texture[state]);
					break;
				default:
					break;
			}
			break;
		case 10:
			switch (dir) {
				case Left:
					state = 2;
					sprite.setTexture(texture[state]);
					break;
				case Up:
					state = 2;
					sprite.setTexture(texture[state]);
					break;
				case Right:
				{
					Coord next(speed + pos.x, pos.y);
					if (!checkCollision(barrels, sandbags, nb, ns, next)) {
						state = 2;
						sprite.setTexture(texture[state]);
						setPosition(next);
					}
				}
					break;
				case Down:
					state = 2;
					sprite.setTexture(texture[state]);
					break;
				default:
					break;
			}
			break;
		case 11:
			switch (dir) {
				case Left:
					state = 4;
					sprite.setTexture(texture[state]);
					break;
				case Up:
					state = 4;
					sprite.setTexture(texture[state]);
					break;
				case Right:
					state = 4;
					sprite.setTexture(texture[state]);
					break;
				case Down:
				{
					Coord next(pos.x, speed + pos.y);
					if (!checkCollision(barrels, sandbags, nb, ns, next)) {
						state = 4;
						sprite.setTexture(texture[state]);
						setPosition(next);
					}
				}
					break;
				default:
					break;
			}
			break;
		case 12:
			switch (dir) {
				case Left:
				{
					Coord next(-speed + pos.x, pos.y);
					if (!checkCollision(barrels, sandbags, nb, ns, next)) {
						state = 6;
						sprite.setTexture(texture[state]);
						setPosition(next);
					}
				}
					break;
				case Up:
					state = 6;
					sprite.setTexture(texture[state]);
					break;
				case Right:
					state = 6;
					sprite.setTexture(texture[state]);
					break;
				case Down:
					state = 6;
					sprite.setTexture(texture[state]);
					break;
				default:
					break;
			}
			break;
		case 13:
			switch (dir) {
				case Left:
				{
					Coord next(-speed + pos.x, pos.y);
					if (!checkCollision(barrels, sandbags, nb, ns, next)) {
						state = 6;
						sprite.setTexture(texture[state]);
						setPosition(next);
					}
				}
					break;
				case Up:
					state = 6;
					sprite.setTexture(texture[state]);
					break;
				case Right:
					state = 6;
					sprite.setTexture(texture[state]);
					break;
				case Down:
					state = 6;
					sprite.setTexture(texture[state]);
					break;
				default:
					break;
			}
			break;
		default:
			break;
	}
}

//Spawn player randomly after killed
void Player::randomSpawn(Player& other, Barrel *barrels, Sandbag *sandbags, int nb, int ns) {
	bool spawned = false;		//This parameter is used to store spawn information,
	bool keepgoing;				//This parameter is used to go to outer loop from inside loop
	int new_x;					//New x coordinate
	int new_y;					//New y coordinate
	srand(time(NULL));			//Intializes random number generator
	while (!spawned) {
		new_x = rand() % (static_cast<int>(window->getSize().x) - static_cast<int>(sprite.getGlobalBounds().width));	//generate random number from 0 to (window width size - sprite width size)
		new_y = rand() % (static_cast<int>(window->getSize().y) - static_cast<int>(sprite.getGlobalBounds().height));	//generate random number from 0 to (window height size - sprite heigth size)
		cout << "new x: " << new_x << " " << "new y " << new_y << endl;
		//if new position is close to old one, pick another random position
		if ((pos.x >= new_x - 200) && (pos.x <= new_x + 200) && (pos.y >= new_y - 200) && (pos.y <= new_y + 200)) {		
			continue;
		}
		//if new position is close to other player, pick another random position
		if ((other.getPosition().x >= new_x - 200) && (other.getPosition().x <= new_x + 200) && (other.getPosition().y >= new_y - 200) && (other.getPosition().y <= new_y + 200)) {
			continue;
		}
		keepgoing = true;
		//if there is a collision between one of the visible barrels go to outer loop
		for (int i = 0; i < nb && keepgoing; i++) {
			if (barrels[i].getVisible() && (new_x + 100 >= barrels[i].getPosition().x) && (new_x - 100 <= barrels[i].getPosition().x) && (new_y + 100 >= barrels[i].getPosition().y) && (new_y - 100<= barrels[i].getPosition().y)) {
				keepgoing = false;
				spawned = false;
			}
			else {
				spawned = true;
			}
		}
		//if there is a collision between one of the sandbags go to outer loop
		for (int i = 0; i < ns && keepgoing; i++) {
			if ((new_x + 100 >= sandbags[i].getPosition().x) && (new_x - 100 <= sandbags[i].getPosition().x) && (new_y + 100 >= sandbags[i].getPosition().y) && (new_y - 100 <= sandbags[i].getPosition().y)) {
				keepgoing = false;
				spawned = false;
			}
			else {
				spawned = true;
			}
		}
	}

	//random location is chosen correctly, update position and texture
	pos.x = new_x;
	pos.y = new_y;
	sprite.setPosition(pos.x, pos.y);
	sprite.setTexture(texture[0]);
	state = 0;
	s = 0;
}

//Reset parameters after game restart
void Player::startAgain(Coord pos) {
	sprite.setTexture(texture[0]);
	setPosition(pos);
	state = 0;
	s = 0;
	score = 0;
}

//Set speed of player
void Player::setSpeed(float s) {
	speed = s;
}

//Increments score of the player
void Player::incrementScore(void) {
	score++;
}

//Returns the current score of the player
int Player::getScore(void) {
	return score;
}

//Returns the current state of the player
int Player::getState(void) {
	return state;
}

//Returns the current position of the player
Coord Player::getPosition(void) {
	return pos;
}

//Set if walking key is pressed
void Player::setPressed(WalkDirection d, bool p) {
	switch (d) {
	case Player::Left:
		leftpressed = p;
		break;
	case Player::Up:
		uppressed = p;
		break;
	case Player::Right:
		rightpressed = p;
		break;
	case Player::Down:
		downpressed = p;
		break;
	default:
		break;
	}
}

//Set if shooting key is pressed
void Player::setShoot(bool s) {
	shoot = s;
}

//destructor of player to deallocate memory
Player::~Player() {
	delete[] texture;
}