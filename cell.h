#ifndef _CELL_H_
#define _CELL_H_

#include "controller.h"
#include <string>

class Game;

class Cell{
	std::string name;
	Game* game;
public:
	Cell(std::string);
	void setGame(Game *game);
};

#endif