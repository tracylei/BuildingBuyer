#ifndef _GAME_H_
#define _GAME_H_


#include "bank.h"
#include "dice.h"
#include "cell.h"

#include <vector>

using namespace std;

const int MAX_IMPROVEMENTS = 5;
const int GRID_SIZE = 40;

class Player;
class Controller;
class Property;

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
public:
	Dice* die1;
	Dice* die2;
	Game();
	// ~Game();
	//void save();
	Player* getCurrentPlayer();
	Player* getPlayer(int p);
	Player* getPlayer(string s);
	Property* getProperty(string name);
	Cell* getTheGrid(int i);

	bool getTestMode();
	void play();
	void endTurn();
	int rollDie1();
	int rollDie2();
	Bank* getBank();
	void refreshBoard();
	static void reclaimTimCups(int n);
	static int getTimCupCount();
	// static void incrRollUpCount();
	// static int getRollUpCount();
	// //notify the controller that improvements were built on this property
	// // void notifyImprove(Property* p);
	int getNumPlayers();
	void addPlayer (Player* p);
	// void removePlayer (Player* p);
	bool isWon();

	//Called by the player to notify the controller of its change in position
	void notify(Player* p, int prevPos, int curPos);
	//Notify a cell that a player has landed on it
	void notifyCell(int);
	//Called by a property to notify the game to notify the controller that an improvement was built/sold
	void notifyImprove(int, int numImprov);
	void init(Controller* controller);

	void save(string);
	void setTestingMode(bool mode);
};


#endif
