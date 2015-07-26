#ifndef _PROPERTY_H_
#define _PROPERTY_H_

#include "cell.h"
#include "owner.h"
#include "player.h"
#include <string>

class Property : public Cell{
	Owner* owner;
	int cost, numImpr;
	bool mortgaged;
	std::string block;

	//From super class - string name;
public:
	Property(std::string name, std::string block, int cost);
	Property(std::string name, int cost);
	int getImpr();
	int getCost();
	bool isMortgaged();
	// //Returns false if purchase was unsuccessful
	void setOwner(Owner* newOwner);
	Owner* getOwner(); 
	// virtual void chargeFee(Player* p)=0;
	// //void auction(input stream);
	void buy(Player* buyer);
};

#endif


