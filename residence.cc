#include "residence.h"

using namespace std;

Residence::Residence(string bldgName, int *rentFee): Property(bldgName, 200),rent(rentFee){
	//Note index corresponds to number of residences owned
}

// void Residence::chargeFee(Player* p){
// 	p->pay(rent[p->getNumRezOwned()]);
// }

