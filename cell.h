#ifndef _CELL_H_
#define _CELL_H_

#include "controller.h"
#include <string>

class Game;

class Cell{
	Game* game;
protected:
	std::string name;
public:
	Cell(std::string);
	void setGame(Game *game);
	string getName();
};

#endif