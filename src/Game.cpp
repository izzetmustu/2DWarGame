#include "Game.h"

//constructor, create window, objects and draw them
Game::Game(float speed, int w, int h, int nb, int ns, int np) {
	//game status is open and start the other parameters
	game_open = true;
	this->speed = speed;
	width = w;
	height = h;
	numBarrels = nb;
	numSandbags = ns;
	numPlayers = np;

	//create window
	this->window = new sf::RenderWindow(sf::VideoMode(width, height), "2D TPS");
	bgTexture.loadFromFile("textures/grass.png");	//load background texture
	bgTexture.setRepeated(true);					//if window size is bigger than the texture size repeat it to fill up the window
	bgSprite.setTexture(bgTexture);					//load the texture to background sprite
	bgSprite.setTextureRect(sf::IntRect(0, 0, width, height));		//fill up the window background with texture
	window->setVerticalSyncEnabled(true);							//it is used to avoid screen tearing
	window->setFramerateLimit(60);									//since the fps is much more than the monitor refresh rate for fast game, we need to limit the fps so that we can see the updates on the screen
	
	string path = "textures/";			//default basepath for all the textures

	barrels = new Barrel[numBarrels];	//create barrels
	sandbags = new Sandbag[numSandbags];	//create sandbags
	players = new Player[numPlayers];		//create players
	bullets = new BulletList(this->window, path);

	//initialization of barrels
	barrels[0].init(window, path, Coord(180, 150));
	barrels[1].init(window, path, Coord(360, 300));
	barrels[2].init(window, path, Coord(450, 450));
	barrels[3].init(window, path, Coord(720, 600));
	barrels[4].init(window, path, Coord(900, 750));

	//initialization of sandbags
	sandbags[0].init(window, path, Coord(180, 750));
	sandbags[1].init(window, path, Coord(360, 600));
	sandbags[2].init(window, path, Coord(630, 450));
	sandbags[3].init(window, path, Coord(720, 300));
	sandbags[4].init(window, path, Coord(900, 150));

	//initialization of players
	players[0].init(window, path, Coord(540, 480));
	players[1].init(window, path, Coord(540, 240));
	players[0].setSpeed(speed * 10);
	players[1].setSpeed(speed * 10);
	players[0].walk(Player::WalkDirection::Right, barrels, sandbags, numSandbags, numBarrels);
	players[0].walk(Player::WalkDirection::Right, barrels, sandbags, numSandbags, numBarrels);
	players[0].walk(Player::WalkDirection::Down, barrels, sandbags, numSandbags, numBarrels);
	players[0].walk(Player::WalkDirection::Down, barrels, sandbags, numSandbags, numBarrels);

	//initialization of texture and font
	font.loadFromFile("font.ttf");
	if (!font.loadFromFile("font.ttf"))
	{
		std::cout << "Font could not opened" << endl;
	}
	text.setFont(font);
	text.setCharacterSize(24);
	text.setPosition(425, 880);					//default scoreboard position
	scoreboard = "\t\t\tScoreboard\nPlayer 1\t\t\t\tPlayer 2\n" + to_string(players[0].getScore()) + "\t\t\t\t\t\t\t\t\t\t" + to_string(players[1].getScore());
	text.setString(scoreboard);

	//draw the screen for all
	refresh();
}

void Game::update() {
	//check all the window's events that were triggered
	sf::Event event;
	while (window->pollEvent(event))
	{
		//check which key is pressed, each player can move only one direction at a time
		if (event.type == sf::Event::KeyPressed)
		{
			//enable player 1 to walk left
			if (event.key.code == sf::Keyboard::Left) {
				players[0].setPressed(Player::WalkDirection::Left, true);
			}
			//enable player 1 to walk right
			else if (event.key.code == sf::Keyboard::Right) {
				players[0].setPressed(Player::WalkDirection::Right, true);
			}
			//enable player 1 to walk up
			else if (event.key.code == sf::Keyboard::Up) {
				players[0].setPressed(Player::WalkDirection::Up, true);
			}
			//enable player 1 to walk down
			else if (event.key.code == sf::Keyboard::Down) {
				players[0].setPressed(Player::WalkDirection::Down, true);
			}
			//enable player 2 to walk left
			if (event.key.code == sf::Keyboard::A) {
				players[1].setPressed(Player::WalkDirection::Left, true);
			}
			//enable player 2 to walk right
			else if (event.key.code == sf::Keyboard::D) {
				players[1].setPressed(Player::WalkDirection::Right, true);
			}
			//enable player 2 to walk up
			else if (event.key.code == sf::Keyboard::W) {
				players[1].setPressed(Player::WalkDirection::Up, true);
			}
			//enable player 2 to walk down
			else if (event.key.code == sf::Keyboard::S) {
				players[1].setPressed(Player::WalkDirection::Down, true);
			}
			//enable player 1 to shoot
			if (event.key.code == sf::Keyboard::Enter) {
				players[0].setShoot(true);
			}
			//enable player 2 to shoot
			if (event.key.code == sf::Keyboard::Space) {
				players[1].setShoot(true);
			}
			//event type is chosen closed, exit the game
			if (event.key.code == sf::Keyboard::Escape) {
				event.type = sf::Event::Closed;
				game_open = false;				//exit the game
			}
		}
		//check which key is released
		if (event.type == sf::Event::KeyReleased) {
			//player 1 stops walking left
			if (event.key.code == sf::Keyboard::Left) {
				players[0].setPressed(Player::WalkDirection::Left, false);
			}
			//player 1 stops walking right
			if (event.key.code == sf::Keyboard::Right) {
				players[0].setPressed(Player::WalkDirection::Right, false);
			}
			//player 1 stops walking up
			if (event.key.code == sf::Keyboard::Up) {
				players[0].setPressed(Player::WalkDirection::Up, false);
			}
			//player 1 stops walking down
			if (event.key.code == sf::Keyboard::Down) {
				players[0].setPressed(Player::WalkDirection::Down, false);
			}
			//player 2 stops walking left
			if (event.key.code == sf::Keyboard::A) {
				players[1].setPressed(Player::WalkDirection::Left, false);
			}
			//player 2 stops walking right
			if (event.key.code == sf::Keyboard::D) {
				players[1].setPressed(Player::WalkDirection::Right, false);
			}
			//player 2 stops walking up
			if (event.key.code == sf::Keyboard::W) {
				players[1].setPressed(Player::WalkDirection::Up, false);
			}
			//player 2 stops walking down
			if (event.key.code == sf::Keyboard::S) {
				players[1].setPressed(Player::WalkDirection::Down, false);
			}
			//player 1 stops shooting
			if (event.key.code == sf::Keyboard::Enter) {
				players[0].setShoot(false);
			}
			//player 2 stops shooting
			if (event.key.code == sf::Keyboard::Space) {
				players[1].setShoot(false);
			}
		}

		// close the window if event type is closed
		if (event.type == sf::Event::Closed) {
			window->close();
		}
	}
	//take appropriate action for players and refresh the window
	action();

	/* ALTERNATIVE APPROACH FOR KEY PRESSED AND KEY RELEASED EVENTS */
	////walk left player 1
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
	//	players[0].walk(Player::WalkDirection::Left, barrels, sandbags, numSandbags, numBarrels);
	//}
	////walk right player 1
	//else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
	//	players[0].walk(Player::WalkDirection::Right, barrels, sandbags, numSandbags, numBarrels);
	//}
	////walk up player 1
	//else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
	//	players[0].walk(Player::WalkDirection::Up, barrels, sandbags, numSandbags, numBarrels);
	//}
	////walk down player 1
	//else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
	//	players[0].walk(Player::WalkDirection::Down, barrels, sandbags, numSandbags, numBarrels);
	//}
	////walk left player 2
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
	//	players[1].walk(Player::WalkDirection::Left, barrels, sandbags, numSandbags, numBarrels);
	//}
	////walk right player 2
	//else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
	//	players[1].walk(Player::WalkDirection::Right, barrels, sandbags, numSandbags, numBarrels);
	//}
	////walk up player 2
	//else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
	//	players[1].walk(Player::WalkDirection::Up, barrels, sandbags, numSandbags, numBarrels);
	//}
	////walk down player 2
	//else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
	//	players[1].walk(Player::WalkDirection::Down, barrels, sandbags, numSandbags, numBarrels);
	//}

	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
	//	bullets->add(players[0].getPosition(), players[0].getState(), speed);
	//}
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
	//	bullets->add(players[1].getPosition(), players[1].getState(), speed);
	//}
	//refresh();
	//checkScore();
	////event type is chosen closed, exit the game
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
	//	event.type = sf::Event::Closed;
	//	game_open = false;				//exit the game
	//}
}

//check game is still open
bool Game::isGameOpen() {
	return game_open;
}

//refresh the drawing for all
void Game::refresh() {
	//first clear the window, if we don't we see all the movements on the screen
	window->clear(sf::Color::Black);
	window->draw(bgSprite);		//draw background first
	//draw barrels, sanbags and players
	for (int i = 0; i < numBarrels; i++) {
		if (barrels[i].getVisible()) {
			barrels[i].paint();
		}
	}
	for (int i = 0; i < numSandbags; i++) {
		sandbags[i].paint();
	}
	for (int i = 0; i < numPlayers; i++) {
		players[i].paint();
	}
	bullets->checkCollision(players, barrels, sandbags, numPlayers, numBarrels, numSandbags);			//check collision before bulletlist update(draw and move)
	bullets->update();																					//bulletlist update(draw and move)
	scoreboard = "\t\t\tScoreboard\nPlayer 1\t\t\t\tPlayer 2\n" + to_string(players[0].getScore()) + "\t\t\t\t\t\t\t\t\t\t" + to_string(players[1].getScore());		//update scoreboard
	text.setString(scoreboard);			//update text
	window->draw(text);					//draw the text
	window->display();					//display, make them visible on the screen(take the values from buffer and send to screen to output)
}

//if one of the players score is 10, reset the game or exit
void Game::checkScore() {
	if (players[0].getScore() == 10) {
		reset(0);
	}
	else if (players[1].getScore() == 10) {
		reset(1);
	}
}

//Reset the game if one of the player wants to start over or exit
void Game::reset(int winner) {
	text.setPosition(380, 440);
	scoreboard = "Player " + to_string(winner+1) + " wins, start over? (Y/N)";
	text.setString(scoreboard);
	window->clear(sf::Color::Black);
	window->draw(bgSprite);		//draw background first
	window->draw(text);
	window->display();
	bool stop = true;
	while (stop) {
		//if yes, start over
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y)) {
			//make visible barrel objects
			for (int i = 0; i < numBarrels; i++) {
				barrels[i].setVisible(true);
			}
			text.setPosition(425, 880);																	//default scoreboard position
			bullets->deleteList();																		//delete bullet list
			players[0].startAgain(Coord(540, 480));														//make players parameters default 
			players[1].startAgain(Coord(540, 240));		
			players[0].walk(Player::WalkDirection::Right, barrels, sandbags, numSandbags, numBarrels);
			players[0].walk(Player::WalkDirection::Right, barrels, sandbags, numSandbags, numBarrels);
			players[0].walk(Player::WalkDirection::Down, barrels, sandbags, numSandbags, numBarrels);
			players[0].walk(Player::WalkDirection::Down, barrels, sandbags, numSandbags, numBarrels);		
			refresh();																					//draw the updates
			stop = false;
		} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::N)) {										//if no, exit
			stop = false;
			game_open = false;
		}
	}
}

//take appropriate action, refresh the window and check the score, if-else statement is applied for each player so that he can move only one direction at a time
void Game::action() {
	for (int i = 0; i < numPlayers; i++) {
		if (players[i].uppressed) {
			players[i].walk(Player::WalkDirection::Up, barrels, sandbags, numSandbags, numBarrels);
		}
		else if (players[i].downpressed) {
			players[i].walk(Player::WalkDirection::Down, barrels, sandbags, numSandbags, numBarrels);
		}
		else if (players[i].leftpressed) {
			players[i].walk(Player::WalkDirection::Left, barrels, sandbags, numSandbags, numBarrels);
		}
		else if (players[i].rightpressed) {
			players[i].walk(Player::WalkDirection::Right, barrels, sandbags, numSandbags, numBarrels);
		}
		if (players[i].shoot) {
			bullets->add(players[i].getPosition(), players[i].getState(), speed);
		}
		refresh();				//These functions needs to be here not to jump any steps
		checkScore();
	}
}

//destructor, we need to release the memory which we allocate dynamically
Game::~Game() {
	delete[] barrels;
	delete[] sandbags;
	delete[] players;
	bullets->deleteList();
	delete window;
}