#ifndef __CELLDISPLAY_H__
#define __CELLDISPLAY_H__

#include <iostream>
#include <iomanip>
#include <string>

class CellDisplay{
	std::string name;
	bool isProperty;
	int id, numImprov;
	char players[8]; //max number of players
public:
	CellDisplay();
	CellDisplay(std::string name, int id, int isProperty, int numImpr); // name, id, isProperty, numImpr
	
	std::string getName();
	bool getIsProperty();
	char* getPlayers();
	int getImpr();

	void setPlayer(char);
	void removePlayer(char);
	void addImpr();
	void sellImpr();
};

#endif
