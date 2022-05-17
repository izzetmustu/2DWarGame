#include "Barrel.h"
#include "Sandbag.h"

#pragma once
using namespace std;

class Player : public Object {
private:
	int state;						//Primary state of the player 
	int s;							//Secondary state variable
	int score;						//Score of the player
	float speed;
public:
	//Players walking direction states and shooting state
	bool uppressed;
	bool downpressed;
	bool leftpressed;
	bool rightpressed;
	bool shoot;

	//walking directions are specified
	enum WalkDirection {
		Left,
		Up,
		Right,
		Down
	};

	void init(sf::RenderWindow *window, string textBasePatch, Coord pos);							//Initializes player object
	void setPosition(Coord pos);																	//Sets player position
	//next_pos added, if the next position is of player inside the other objects, dont move that way. also player cant go out the window
	bool checkCollision(Barrel *barrels, Sandbag *sandbags, int nb, int ns, Coord next_pos);		
	void walk(WalkDirection dir, Barrel *barrels, Sandbag * sandbags, int nb, int ns);				//Moves the player around		
	void incrementScore(void);																		//Increments score of the player
	int getScore(void);																				//Returns the current score of the player
	int getState(void);																				//Returns the current state of the player
	Coord getPosition(void);																		//Returns the current position of the player
	void randomSpawn(Player& other, Barrel *barrels, Sandbag *sandbags, int nb, int ns);			//Spawn player randomly after killed
	void startAgain(Coord pos);																		//Reset parameters after game restart
	void setSpeed(float s);																			//Set speed of player
	void setPressed(WalkDirection d, bool p);														//Set if walking key is pressed
	void setShoot(bool s);																			//Set if shooting key is pressed
	~Player();																						//destructor of player to deallocate memory
};

