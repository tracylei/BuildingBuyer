#include "residence.h"

using namespace std;

Residence::Residence(string bldgName): Property(bldgName, 200, false){
	rent = new int [4];
}

Residence::~Residence(){
	delete [] rent;
}


void Residence::doAction(Player* p){
	if (owner->getName()!= "BANK" && static_cast<Player*>(owner)->getSymbol()!=p->getSymbol()){
		if (mortgaged){
			cout<<"You were not charged for landing on "<<name<<" because it is currently mortgaged."<<endl;

		}else {
			cout<<"You will be charged $"<<rent[p->getNumRezOwned()];
			cout<<" in rent by "<<owner->getName()<<", the owner of "<<name<<"."<<endl;		
			p->pay(rent[static_cast<Player*>(owner)->getNumRezOwned()], owner);
		}
	}
}


int Residence::getValue(){
	return cost;
}

void Residence::setRent(int index, int rentFee){
	rent[index] = rentFee;

}
