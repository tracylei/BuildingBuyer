#ifndef _PROPERTY_H_
#define _PROPERTY_H_

#include "cell.h"
#include <string>

class Property : public Cell{
	Owner* owner;
	int cost, numImpr;
	bool mortgaged;
	string block;

	//From super class - string name;
public:
	Property(string name, string block, int cost);
	Property(string name, int cost);
	int getImpr();
	// //Returns false if purchase was unsuccessful
	void setOwner(Owner* newOwner);
	Owner* getOwner(); 
	// virtual void chargeFee(Player* p)=0;
	// //void auction(input stream);
	// void buy(Player* buyer);
	// int mortgage(Player* p);
};

#endif


