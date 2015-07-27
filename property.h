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
	Property(std::string name, std::string block, int cost);
	Property(std::string name, int cost);
	int getImpr();
	virtual int getValue()=0;
	
	int getCost();
	bool isMortgaged();

	void setMortgaged(bool);
	// //Returns false if purchase was unsuccessful
	void setOwner(Owner* newOwner);
	Owner* getOwner(); 
	// //void auction(input stream);
	void buy(Player* buyer);
	void buy(Player* buyer, int bid); //for buying auctioned properties
	virtual void doAction(Player* p)=0;
	void auction(int numBidders, vector<Player*> bidder, string master);
};

#endif


