#include <iostream>
#include "academicbuilding.h"

AcademicBuilding::AcademicBuilding(std::string name, int cost, std::string block, int improvCost, int *tuition):
								Property(name, block, cost),imprCost(improvCost),tuition(tuition){
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



// void AcademicBuilding::chargeFee(Player* p){
// 	p->pay(tuition);
// }


