#include "residence.h"

using namespace std;

Residence::Residence(string bldgName, int *rentFee): Property(bldgName, 200),rent(rentFee){
	//Note index corresponds to number of residences owned
}

int Residence::getRent(){
	cout<<"You will be charged $"<<rent[p->getNumRezOwned()];
	cout<<" in rent by "<<owner->getName()<<", the owner of "<<name<<"."<<endl;		
	return rent[owner->getNumRezOwned()];
}

