#include "residence.h"

using namespace std;

Residence::Residence(string bldgName, int cost, int *rentFee): Property(bldgName, cost),rent(rentFee){
	//Note index corresponds to number of residences owned
}

// void Residence::chargeFee(Player* p){
// 	p->pay(rent[p->getNumRezOwned()]);
// }

