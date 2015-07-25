#ifndef __PLAYER_H_
#define __PLAYER_H_
#include "dice.h"
#include "game.h"
#include "owner.h"
#include "property.h"

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

// class Game;
// class Property;

class Player : public Owner{
	Game *game;
	string name;
	char symbol;
	int curPosition, timCups;
<<<<<<< HEAD
	// vector<Property*> properties;
=======
	vector<Property*> properties;
>>>>>>> 4356b80691a7f0e3439b247fdc2236c788c41869
	bool inJail;
	int turnsInJail;
	int jailRoll1;
	int jailRoll2;
public:
	Player();
	Player(Game* game, string name, char symbol, int position, int cash, int timsCups); //for loading from file

	string getName(); //returns name of player
	char getSymbol();
	int getCash();
	int getPos();
<<<<<<< HEAD
	int getTimCups();
	void useTimCup();
	int getTurnsInJail();
	void setJailRolls(int roll1, int roll2);
	bool isInJail();
	void addCash(int x); //inherited
	// vector<Property*> getProperties();

=======
	int isInJail();
	vector<Property*> getProperties();

	void addCash(int x); //inherited
	void addProperty(Property*);

>>>>>>> 4356b80691a7f0e3439b247fdc2236c788c41869
	void play();
	void roll();
	// void next();
	void move();
	void move(int r1, int r2);
	void goToJail();
	void leaveJail();
	
	bool pay(int, Player*); //return true is payment successful, else false
	void declareBankrupt();
	void displayAssets();
	
	bool trade(Player*, string, string);
	bool acceptTrade(Player*, string, string);

 //    void buy(Property*);
	// void mortgage(Property*);
	// void unmortgage(Property*);


};

#endif