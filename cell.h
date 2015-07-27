#ifndef _CELL_H_
#define _CELL_H_

#include <string>

class Game;
class Player;


class Cell{
protected:
	std::string name;
	Game* game;
	int index;
	bool buyable;
	bool academic;
public:
	Cell(std::string, bool, bool);
	void setGame(Game *game);
	void setIndex(int);
	std::string getName();
	int getID();
	bool isBuyable();
	bool isAcademic();
	virtual void doAction(Player* p) = 0;
};

#endif