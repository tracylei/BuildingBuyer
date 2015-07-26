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
public:
	Cell(std::string);
	void setGame(Game *game);
	void setIndex(int);
	std::string getName();
	int getID();
	virtual void doAction(Player* p) = 0;
};

#endif