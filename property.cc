#include "property.h"
#include <iostream>

using namespace std;

Property::Property(string name, string block, int cost, bool academic): Cell(name, true, academic), cost(cost), block(block){
	mortgaged = false;
	numImprov = 0;
	feeRate = 0.6;
}

Property::Property(string name, int cost, bool academic): Cell(name, true, academic), cost(cost){
	mortgaged = false;
	numImprov = 0;
	feeRate = 0.6;
}

int Property::getImpr(){
	return numImprov;
}

Owner* Property::getOwner(){
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


void Property::setFeeRate(double rate){
	feeRate = rate;
}

double Property::getFeeRate(){
	return feeRate;
}

void Property::auction(int numBidders, vector<Player*> bidders, string master){
	//int bid = cost / 4; //starting bid is 25% of cost of property
	cout <<"Starting the Auction for " << getName() << " at $1." << endl;
	int bid = 1;
	bool bidOccurred = false;

	vector<Player*>::iterator it = bidders.begin();
	while(numBidders > 1 || (numBidders==1&&!bidOccurred)){

			string action, input;
			cout << "The ask price for the property is currently at $"<<bid<<"."<<endl;
			cout << (**it).getName() << ", would you like to bid or pass?";
			cout <<" You currently have $"<<(**it).getCash()<<" in cash."<<endl;
			cout <<"Please only use the \"bid\" or \"pass\" command where \"bid\" should be followed by your bid (ex. bid 25)." << endl;

			getline(cin, input);
			istringstream iss(input);
			iss>>action;

			while(action!="pass"){
				if (action == "bid"){
					int tempBid;
					iss>>tempBid;	
					if (tempBid > bid || (!bidOccurred&&tempBid==1)){
						bid = tempBid;
						break;
					}else{
						cout<<"You must bid a highed price than the current price of $"<<bid<<"."<<endl;
					}
				}else{
					cout << "Invalid input. Please only use the \"bid\" or \"pass\" command." << endl;
				}
				getline(cin, input);
				istringstream iss(input);
				iss>>action;
			}
			

			if(action == "bid"){
				bidOccurred=true;
				cout << (**it).getName() << " has bid, the price is now $" << bid <<"."<< endl;
				it++;
			}else if (action == "pass"){
				--numBidders;
				cout << (**it).getName() << " has withdrawn from the auction." << endl;
				it = bidders.erase(it);
			}
			if (it == bidders.end())
				it=bidders.begin();
	}

	if (bidOccurred){
		Player *winner = bidders.at(0);
		cout << winner->getName() << " has won the property for $" << bid << "."<<endl;
		this->buy(winner, bid);
	}else{
		cout<<"No one bid for the property so it will remain unowned."<<endl;
	}

}

//Buyer buys this property, assumes pay method will take care of
//bankruptcy etc.
void Property::buy(Player* buyer){

	if(buyer->pay(cost, static_cast<Player*>(owner))){
		owner = buyer;
		buyer->addProperty(this);
	}
}

//Buyer buys the property, for winning bid price
void Property::buy(Player* buyer, int bid){

	if(buyer->pay(bid, static_cast<Player*>(owner))){
		owner = buyer;
		buyer->addProperty(this);
	}
}

