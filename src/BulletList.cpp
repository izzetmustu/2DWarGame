#include "BulletList.h"

//Constructor for the BulletList
BulletList::BulletList(sf::RenderWindow* window, string texturepath) {	//Constructor for the BulletList
	list = nullptr;
	this->window = window;
	this->path = texturepath;			//default basepath for all the textures
	counter = 0;						
}

//Adds a new bullet to the list, s parameter is added for speed
void BulletList::add(Coord Pos, int state, float s) {
	if (list == nullptr) {
		list = new Bullet;
		list->init(this->window, this->path, Pos, state);
		list->setSpeed(50*s);
		list->next = nullptr;
		std::cout << "Created new list " << ++counter << endl;
	}
	else {
		Bullet* tmp = list;
		while (tmp != nullptr) {
			if (tmp->next == nullptr) {
				tmp->next = new Bullet;
				tmp->next->init(this->window, this->path, Pos, state);
				tmp->next->setSpeed(50*s);
				tmp->next->next = nullptr;
				std::cout << "Added " << ++counter << endl;
				break;
			}
			tmp = tmp->next;
		}
	}
	
}			

//Draws every bullet in the list and then moves them
void BulletList::update(void) {					
	Bullet* tmp = list;
	while (tmp != nullptr) {
		tmp->paint();
		tmp->move();
		tmp = tmp->next;
	}
}

//Checks whether a bullet in the list collided with other objects or with the edge of the screen
void BulletList::checkCollision(Player* players, Barrel* barrels, Sandbag* sandbags, int np, int nb, int ns) {
	Bullet* tmp = list;
	bool bulletchanged;				//This parameter is used to go to outer loop from inside loop. if a bullet is deleted, choose next bullet in the list and go to outer loop
	while (tmp != nullptr) {
		bulletchanged = false;
		//Player collision detection
		for (int i = 0; i < np && bulletchanged == false; i++) {
			if ((tmp->pos.x >= players[i].getPosition().x) && (tmp->pos.x <= players[i].getPosition().x + 100) && (tmp->pos.y >= players[i].getPosition().y) && (tmp->pos.y + 10 <= players[i].getPosition().y + 100)) {
				Bullet* deleted = tmp;
				tmp = tmp->next;
				deleteBullet(deleted);
				if (i == 0) {				//if there is a collision between player 1, increment score of player 2, respawn player 1
					players[1].incrementScore();
					players[0].randomSpawn(players[1], barrels, sandbags, nb, ns);
				}
				else {						//if there is a collision between player 2, increment score of player 1, respawn player 2
					players[0].incrementScore();
					players[1].randomSpawn(players[0], barrels, sandbags, nb, ns);
				}
				if (players[i].getScore() == 10) return;		//if the score of the player becomes 10, don't check next bullet exit from function
				bulletchanged = true;
			}
		}
		//Barrel collision detection
		for (int i = 0; i < nb && bulletchanged == false; i++) {
			if (barrels[i].getVisible() && (tmp->pos.x >= barrels[i].getPosition().x) && (tmp->pos.x <= barrels[i].getPosition().x + 60) && (tmp->pos.y >= barrels[i].getPosition().y) && (tmp->pos.y + 10 <= barrels[i].getPosition().y + 60)) {
				barrels[i].setVisible(false);
				Bullet* deleted = tmp;
				tmp = tmp->next;
				deleteBullet(deleted);
				bulletchanged = true;
			}
		}
		//Sandbag collision detection
		for (int i = 0; i < ns && bulletchanged == false; i++) {
			if ((tmp->pos.x >= sandbags[i].getPosition().x) && (tmp->pos.x <= sandbags[i].getPosition().x + 60) && (tmp->pos.y >= sandbags[i].getPosition().y) && (tmp->pos.y + 10 <= sandbags[i].getPosition().y + 70)) {
				Bullet* deleted = tmp;
				tmp = tmp->next;
				deleteBullet(deleted);
				bulletchanged = true;
			}
		}

		//window boundaries
		if (bulletchanged == false && (tmp->pos.x <0 || tmp->pos.x > window->getSize().x || tmp->pos.y < 0 || tmp->pos.y > window->getSize().y)) {
			Bullet* deleted = tmp;
			tmp = tmp->next;
			deleteBullet(deleted);
			bulletchanged = true;
		}
		if (tmp != nullptr) tmp = tmp->next;
	}
}

//Delete the bullet that that collided
void BulletList::deleteBullet(Bullet* deleted) {
	Bullet* d = list;
	if (list != nullptr) {
		if (list == deleted) {
			list = list->next;
			delete d;
			d = nullptr;
		}
		else {
			while (d->next != nullptr) {
				if (d->next == deleted) {
					d->next = deleted->next;
					delete deleted;
					break;
				}
				d = d->next;
			}
		}
	}
	else {
		std::cout << "No bullet in the list" << endl;
	}
	std::cout << "Deleted " << --counter << endl;
}

//Delete entire linked list
void BulletList::deleteList() {
	Bullet* tmp = list;
	while (tmp != nullptr) {
		list = list->next;
		delete tmp;
		tmp = list;
	}
	counter = 0;
	std::cout << "Deleted all the list " << counter << endl;
}