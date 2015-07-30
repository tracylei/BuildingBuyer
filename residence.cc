#include "residence.h"

using namespace std;

Residence::Residence(string bldgName): Property(bldgName, 200, false){
	rent = new int [4];
	rent [0] = 25;
	rent [1] = 50;
	rent [2] = 100;
	rent [3] = 200;
}

Residence::~Residence(){
	delete [] rent;
}

void Residence::doAction(Player* p){
	if (owner->getName()!= "BANK" && static_cast<Player*>(owner)->getSymbol()!=p->getSymbol()){
		if (mortgaged){
			cout<<"You were not charged for landing on "<<name<<" because it is currently mortgaged."<<endl;

		}else {
			int fee = rent[static_cast<Player*>(owner)->getNumRezOwned()-1];
			cout<<"You will be charged $"<<fee;
			cout<<" in rent by "<<owner->getName()<<", the owner of "<<name<<"."<<endl;		
			p->pay(fee, owner);
		}
	}
}


int Residence::getValue(){
	return cost;
}
