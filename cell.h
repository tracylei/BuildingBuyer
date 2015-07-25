#ifndef _CELL_H_
#define _CELL_H_

#include <string>

class Game;

class Cell{
	Game* game;
	int index;
protected:
	std::string name;
public:
	Cell(std::string);
	void setGame(Game *game);
	void setIndex(int);
	std::string getName();
	int getID();

};

#endif