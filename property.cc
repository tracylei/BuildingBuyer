#include "property.h"
#include <iostream>

using namespace std;

Property::Property(string name, string block, int cost): Cell(name), cost(cost), block(block){
	mortgaged = false;
}

Property::Property(string name, int cost): Cell(name), cost(cost){
	mortgaged = false;
}

int Property::getImpr(){
	return numImprov;
}


Owner* Property::getOwner(){
	//cout<<owner->getName()<<endl;
	return owner;
}
int Property::getCost(){
	return cost;
}

bool Property::isMortgaged(){
	return mortgaged;
}

void Property::setOwner(Owner* newOwner){
 	owner=newOwner;
}

void Property::setMortgaged(bool v){
	mortgaged = v;
}
//Buyer buys this property, assumes pay method will take care of
//bankruptcy etc.
void Property::buy(Player* buyer){
	cout << "Would you like to buy " << getName() << " for " << cost << "?(y/n)" << endl;
	
	while(true){
		string resp;
		getline(cin, resp);

		if (resp == "y"){
			if(buyer->pay(cost, static_cast<Player*>(owner))){
				owner = buyer;
				buyer->addProperty(this);
				break;
			}
		}else if(resp == "n"){
			break;
			//call auction
		}
	}
}