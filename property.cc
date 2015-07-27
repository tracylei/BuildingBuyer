#include "property.h"
#include <iostream>

using namespace std;

Property::Property(string name, string block, int cost, bool academic): Cell(name, true, academic), cost(cost), block(block){
	mortgaged = false;
}

Property::Property(string name, int cost, bool academic): Cell(name, true, academic), cost(cost){
	mortgaged = false;
}

int Property::getImpr(){
	return numImprov;
}


Owner* Property::getOwner(){
	//cout<<owner->getName()<<endl;
	return owner;
}

string Property::getOwnerName(){
	return owner->getName();
}
int Property::getCost(){
	return cost;
}

string Property::getBlock(){
	return block;
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
	cout << "Would you like to buy " << getName() << " for $" << cost << "? (y/n)" << endl;
	
	while(true){
		string resp;
		getline(cin, resp);

		while (resp !="y" && resp != "n"){
			cout <<"Please only enter \"y\" for yes and \"n\" for no."<<endl;
			getline (cin, resp);
		}


		if (resp == "y"){
			if(buyer->pay(cost, static_cast<Player*>(owner))){
				buyer->addProperty(this);
				break;
			}
		}else if(resp == "n"){
			break;
			//call auction
		}
	}
}

