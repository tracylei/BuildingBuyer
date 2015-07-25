#ifndef __PLAYER_H_
#define __PLAYER_H_

#include "game.h"
// #include "property.h"

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

// class Game;
// class Property;

class Player{
	Game *game;
	char symbol;
	string name;
	int cash, curPosition, timCups;
	// vector<Property*> properties;
	bool inJail;

public:
	Player();
	Player(string name, char symbol, int position, int cash, int timsCups); //for loading from file

	string getName(); //returns name of player
	char getSymbol();
	int getCash();
	int getPos();
	int isInJail();
	void addCash(int x);
	// vector<Property*> getProperties();


	void play();
	void roll();
	// void next();
	void move();
	void move(int r1, int r2);
	void goToJail();
	
	bool pay(int); //return true is payment successful, else false
	void declareBankrupt();
	void displayAssets();
	
	bool trade(Player*, string, string);
	bool acceptTrade(Player*, string, string);

 //    void buy(Property*);
	// void mortgage(Property*);
	// void unmortgage(Property*);


};

#endif