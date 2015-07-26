#include <iostream>
#include "academicbuilding.h"

AcademicBuilding::AcademicBuilding(std::string name, int cost, std::string block, int improvCost, int *tuition):
								Property(name, block, cost),imprCost(improvCost),tuition(tuition){
	// for (int i = 0; i <= MAX_IMPROVEMENTS; i++){
	// 		cout << tuition[i] << " ";
	// }
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
	cout<<"You will be charged $"<<tuition<<" in tuition by "<<owner->getName()<<", the owner of "<<name<<"."<<endl;
	p->pay(tuition[numImprov], owner);
}

int AcademicBuilding::getValue(){
	return (cost + numImprov*imprCost);
}

