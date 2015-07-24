#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

#include "boarddisplay.h"
#include "game.h"
#include "player.h"

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

	void notify(Player *, int prevPos, int curPos);
	void play();	
	// void loadGame(const std::string);
	// void init(); //calls game init 
};
#endif