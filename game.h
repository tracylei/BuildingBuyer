#ifndef _GAME_H_
#define _GAME_H_



#include "dice.h"
#include "cell.h"

#include <vector>



const int MAX_IMPROVEMENTS = 5;
const int GRID_SIZE = 40;

class Player;
class Owner;
class Controller;
class Property;
class Bank;

class Game{
	Cell** theGrid;
	static Game* game;
	Controller* controller;
	Bank* bank;
	
	std::vector<Player*> players;
	int numPlayers;
	int currPlayer;
	static int rollUpCount;
	bool testMode;
public:
	Dice* die1;
	Dice* die2;
	Game();
	~Game();

	void clearGame();

	Player* getCurrentPlayer();
	Player* getPlayer(int p);
	Player* getPlayer(std::string s);
	std::vector<Player*> getPlayers();
	Property* getProperty(std::string name);
	Cell* getTheGrid(int i);

	bool getTestMode();
	void endTurn();
	int rollDie1();
	int rollDie2();
	Bank* getBank();
	void refreshBoard();

	static void reclaimTimCups(int n);
	static int getTimCupCount();
	static void setTimCupCount(int);
	static void incrRollUpCount();
	static int getRollUpCount();

	int getNumPlayers();
	void addPlayer (Player* p);
	void removePlayer (int symbol);
	bool isWon();
	void endGame();

	void notifyControllerBankrupt(Player* p, Owner* creditor, int amt);

	//Called by the player to notify the controller of its change in position
	void notify(Player* p, int prevPos, int curPos);
	//Notify a cell that a player has landed on it
	void notifyCell(int);
	//Called by a property to notify the game to notify the controller that an improvement was built/sold
	void notifyImprove(int, int numImprov);
	void init(Controller* controller, std::string fname="property.txt"); //initializes game board and cells

	void save(std::string);
	void setTestingMode(bool mode);

};


#endif
