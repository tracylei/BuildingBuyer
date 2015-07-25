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
	string blah;
	CellDisplay cells[40];

public:
	BoardDisplay();
	//map of property and if ownable
	void notify(Player*, int, int); // updates players movements,
	// void notify(Property*); // updates improvements on building
	std::string getblah();
	std::string printPlayers(int);
	std::string printImpr(int);
	void print();

};

#endif