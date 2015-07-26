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

	vector<Property*> properties;

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
	int getTimCups();
	void incrTimCups();

	int getTurnsInJail();
	bool isInJail();
	vector<Property*> getProperties();
	int getNumRezOwned();
	int getNetWorth();

	void addCash(int x); //inherited
	void addProperty(Property*);
	void useTimCup();
	void setJailRolls(int roll1, int roll2);


	void play();
	void roll();
	// void next();
	
	void move();
	void move(int r1, int r2);
	void goToJail();
	void leaveJail();
	
	bool pay(int, Owner*); //return true is payment successful, else false
	void declareBankrupt();
	void displayAssets();
	
	bool trade(Player*, string, string);
	bool acceptTrade(Player*, string, string);

	void mortgage(Property*);
	void unmortgage(Property*);


};

#endif