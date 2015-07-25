#ifndef __BOARDDISPLAY_H__
#define __BOARDDISPLAY_H__

#include "celldisplay.h"
#include "player.h"
// #include "game.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <map>

class BoardDisplay {
	CellDisplay cells[40];

public:
	BoardDisplay();
	//map of property and if ownable
	void notify(Player*, int, int); // updates players movements,
	void notify(int, int); // updates improvements on building
	std::string printPlayers(int);
	std::string printImpr(int);
	void print();

};

#endif