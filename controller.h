#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

#include "boarddisplay.h"
#include "game.h"
#include "player.h"
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
	void play();	
	void loadGame(const std::string);
	// string propNames[40] = {"AL", "SLC", "ML", "TUITION", "ECH", "MKV", "PAS", "NEEDLESHALL", "HH", "DCTimsLine", "RCH", "PAC", "DWE", "CPH", "UWP", "LHI", 
	// 			 "SLC", "BMH", "OPT", "GooseNesting", "EV1", "NEEDLESHALL", "EV2", "EV3", "V1", "PHYS", "B1", "CIF", "B2", "GOTOTIMS", "EIT", "ESC",
	// 			 "SLC", "C2", "REV", "MC", "COOPFEE", "DC"};
	// void init(); //calls game init 
};
#endif