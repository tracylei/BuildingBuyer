#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

#include "boarddisplay.h"
#include "game.h"
#include "player.h"
#include "bank.h"
// #include "property.h"

#include <iostream>
#include <sstream>
#include <string>
#include <map>

class Game;

class Controller{
	Game *game;

	BoardDisplay *board;
	std::map<char, std::string> symbols;
	
public:
	Controller();
	~Controller();
	BoardDisplay *getBoard();
	void refreshBoard ();
	void notify(Player *, int prevPos, int curPos);
	void notifyImprove (int, int numImprov);

	void init(bool testingMode = false, string fname = "property.txt");
	void play(bool);
	void playInJail();
	void rollInJail(int, int);	
	// void loadGame(const std::string);

	void play();	
	void loadGame(const std::string, bool testingMode = false);
	// void init(); //calls game init 
};
#endif