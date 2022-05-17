#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.h"

using namespace std;

int main()
{
	//parameters for game initialization
	float speed = 1;
	int nBarrels = 5;
	int nSandbags = 5;
	int nplayers = 2;
	int width = 1280;
	int height = 960;

	//game conctructor, game is opened
	Game *game = new Game(speed, width, height, nBarrels, nSandbags, nplayers);
	
	//if user does not press esc game is open
	while (game->isGameOpen()) {
		game->update();
	}
	//if game is closed delete it to release memory
	delete game;

	return 0;
}