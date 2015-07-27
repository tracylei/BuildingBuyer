#ifndef _PROPERTY_H_
#define _PROPERTY_H_

#include "cell.h"
#include "owner.h"
#include "player.h"
#include <string>

class Property : public Cell{
protected:
	Owner* owner;
	int cost, numImprov;
	bool mortgaged;
	std::string block;
	//From super class - string name;
public:
	Property(std::string name, std::string block, int cost, bool academic);
	Property(std::string name, int cost, bool academic);
	int getImpr();
	std::string getBlock();
	virtual int getValue()=0;
	
	int getCost();
	bool isMortgaged();

	void setMortgaged(bool);
	// //Returns false if purchase was unsuccessful
	void setOwner(Owner* newOwner);
	Owner* getOwner(); 
	std::string getOwnerName();
	// //void auction(input stream);
	void buy(Player* buyer);
	virtual void doAction(Player* p)=0;

};

#endif


