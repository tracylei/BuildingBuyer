#include "property.h"
#include <iostream>

using namespace std;

Property::Property(string name, string block, int cost, bool academic): Cell(name, true, academic), cost(cost), block(block){
	mortgaged = false;
	numImprov = 0;
}

Property::Property(string name, int cost, bool academic): Cell(name, true, academic), cost(cost){
	mortgaged = false;
	numImprov = 0;
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

void Property::auction(int numBidders, vector<Player*> bidders, string master){
	int bid = cost / 4; //starting bid is 25% of cost of property
	cout <<"Starting Auction for " << getName() << " at initial price of " << bid<<"." << endl;

	while(numBidders > 1){
		for(vector<Player*>::iterator it = bidders.begin(); it != bidders.end(); it++){

			if((**it).getName() == master) {bidders.erase(it);}
			if(bidders.size() == 1) {
				numBidders = 1;
			break;
			}
			string action;
			cout << (**it).getName() << " do you want to bid or pass?" << endl;
			cin >> action;

			if(action == "bid"){
				if (bid+20 > (**it).getCash()){
					cout << "You don't have enough cash to bid." << endl;
					bidders.erase(it);
					--numBidders;
					continue;
				}
				
				bid+= 20;
				cout << (**it).getName() << " has bid, the price is now $" << bid << endl;
			}else if (action == "pass"){
				it = bidders.erase(it);
				--numBidders;
				cout << (**it).getName() << " has passed" << bid<<"." << endl;
			}else{
				cout << "Invalid input. Either use bid or pass." << endl;
			}
		}
	}

	Player *winner = bidders.at(0);
	cout << winner->getName() << " has won the property for $" << bid << endl;
	this->buy(winner, bid);

}

//Buyer buys this property, assumes pay method will take care of
//bankruptcy etc.
void Property::buy(Player* buyer){

	if(buyer->pay(cost, static_cast<Player*>(owner))){
		owner = buyer;
		buyer->addProperty(this);
	}
}

void Property::buy(Player* buyer, int bid){

	if(buyer->pay(bid, static_cast<Player*>(owner))){
		owner = buyer;
		buyer->addProperty(this);
	}
}

