#include "property.h"

using namespace std;

Property::Property(string name, string block, int cost): Cell(name), cost(cost), block(block){
	// owner = new Bank();
	mortgaged = false;
}

Property::Property(string name, int cost): Cell(name), cost(cost){
	// owner = new Bank();
	mortgaged = false;
}

// string Property::getName(){
// 	return name;
// }

int Property::getImpr(){
	return numImpr;
}

// //Buyer buys this property, assumes pay method will take care of
// //bankruptcy etc.
// void Property::buy(Player* buyer){
// 	if (buyer->pay(cost));
// 		owner = buyer;
// }

// void Property::setOwner(Player* newOwner){
// 	owner=newOwner;
// }

// Owner* Property::getOwner(){
// 	return owner;
// }

// int Property::mortgage(){
// 	mortgaged = true;
// 	return cost/2;
// }
