#include "BulletList.h"
#include <string.h>
#include <iostream>
#pragma once
using namespace std;

class Game {
private:
	float speed;					//Game speed
	int numBarrels;					//Number of barrel objects
	int numSandbags;				//Number of sandbag objects
	int numPlayers;					//Number of player objects
	int width;						//Game screen width
	int height;						//Game screen height
	sf::RenderWindow* window;		//SFML window object
	sf::Texture bgTexture;			//Background tile (grass) texture
	sf::Sprite bgSprite;			//Background tile (grass) sprite
	Barrel *barrels;				//Pointer to barrel objects
	Sandbag *sandbags;				//Pointer to sandbag objects
	Player *players;				//Pointer to player objects
	bool game_open;					//this is added to check the game is still open
	BulletList *bullets;			//Pointer to BulletList
	sf::Text text;					//Text object
	sf::Font font;					//Font object
	string scoreboard;				//String for text object
public:
	Game(float speed, int w, int h, int nb, int ns, int np);	//Non-default Constructor
	void update();				//Update game objects and draw
	bool isGameOpen();			//Return game is still open
	void refresh();				//Drawbackground method is deleted, this method refresh the game graphics
	void checkScore();			//If one of the players score is 10, reset the game or exit
	void reset(int winner);		//Reset the game if one of the player wants to start over or exit
	void action();				//Take appropriate action for objects
	~Game();					//Destructor to release the memory which we allocate dynamically
};

