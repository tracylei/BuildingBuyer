#include "residence.h"

using namespace std;

Residence::Residence(string bldgName, int *rentFee): Property(bldgName, 200),rent(rentFee){
	//Note index corresponds to number of residences owned
}

void Residence::doAction(Player* p){
	if (owner->getName()!= "BANK" && owner->getName()!=p->getName()){
		cout<<"You will be charged $"<<rent[p->getNumRezOwned()];
		cout<<" in rent by "<<owner->getName()<<", the owner of "<<name<<"."<<endl;		
		p->pay(rent[static_cast<Player*>(owner)->getNumRezOwned()], owner);
	}
}


int Residence::getValue(){
	return cost;
}


