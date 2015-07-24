#ifndef _GAME_H_
#define _GAME_H_



// #include "dice.h"

#include <vector>

using namespace std;

const int MAX_IMPROVEMENTS = 5;
const int GRID_SIZE = 40;

class Player;
class Controller;
class Cell;

class Game{
	Cell** theGrid;
	static Game* game;
	vector<Player*> players;
	int numPlayers;
	int currPlayer;
	Controller* controller;
	// Dice* dice;
	static int rollUpCount;
public:
	Game();
	// ~Game();
	//void save();
	Player* getCurrentPlayer();
	void next();
	// int rollDice();
	// static void reclaimTimsCups(int n);
	// static void incrRollUpCount();
	// static int getRollUpCount();
	// //notify the controller that improvements were built on this property
	// // void notifyImprove(Property* p);

	void addPlayer (Player* p);
	// void removePlayer (Player* p);
	// bool isWon();



	void init(Controller* controller);
};


#endif
