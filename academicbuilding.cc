#include <iostream>
#include "academicbuilding.h"
#include <unistd.h>

AcademicBuilding::AcademicBuilding(std::string name, int cost, std::string block, int improvCost):
								Property(name, block, cost),imprCost(improvCost){
	tuition = new int [5];
	// for (int i = 0; i <= MAX_IMPROVEMENTS; i++){
	// 		cout << tuition[i] << " ";
	// }

}

void AcademicBuilding::setTuition(int index, int tutCost){
	tuition[index] = tutCost;
}
//Build n improvements
// void AcademicBuilding::improve(int n){
// 	//Check to make sure the owner has a monopoly
// 	//If the owner can sucessfully pay for the improvements
// 	if (owner->hasMonopoly(block)){
// 		if (owner->pay(n*improvCost)){
// 			numImprov++;
// 			game->notifyImprove(this);
// 		}
// 	}
// }



void AcademicBuilding::doAction(Player* p){
	if (owner->getName()!= "bank" && owner->getName()!=p->getName()){
		cout<<"You will be charged $"<<tuition[numImprov]<<" in tuition by "<<owner->getName()<<", the owner of "<<name<<"."<<endl;
		cout<<"Please give "<<owner->getName()<<" a few seconds to collect the tuition.."<<endl;
		usleep(3000000);
		cout<<"You had $"<<p->getCash()<<" before paying, ";
		if (p->pay(tuition[numImprov], owner))
			cout<<"now you have $" <<p->getCash()<<"."<<endl;
	}
}

int AcademicBuilding::getValue(){
	return (cost + numImprov*imprCost);
}

