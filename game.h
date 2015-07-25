#ifndef _GAME_H_
#define _GAME_H_


#include "bank.h"
#include "dice.h"

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
	bool testMode;
	Bank* bank;
	Dice* die1;
	Dice* die2;
public:
	Game();
	// ~Game();
	//void save();
	Player* getCurrentPlayer();
	bool getTestMode();
	void play();
	void endTurn();
	int rollDie1();
	int rollDie2();
	Bank* getBank();
	void refreshBoard();
	static void reclaimTimCups(int n);
	// static void incrRollUpCount();
	// static int getRollUpCount();
	// //notify the controller that improvements were built on this property
	// // void notifyImprove(Property* p);
	void addPlayer (Player* p);
	// void removePlayer (Player* p);
	bool isWon();

	//Called by the player to notify the controller of its change in position
	void notify(Player* p, int prevPos, int curPos);
	void init(Controller* controller);
};


#endif
