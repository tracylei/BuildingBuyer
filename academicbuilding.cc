#include <iostream>
#include "academicbuilding.h"
#include <unistd.h>

AcademicBuilding::AcademicBuilding(std::string name, int cost, std::string block, int improvCost):
								Property(name, block, cost, true),imprCost(improvCost){
	tuition = new int [MAX_IMPROVEMENTS+1];
}

AcademicBuilding::~AcademicBuilding(){
	delete [] tuition;
}

void AcademicBuilding::setTuition(int index, int tutCost){
	tuition[index] = tutCost;
	// for (int i = 0; i <= index; i++){
	// 		cout << tuition[i] << " ";
	// }
}
// Build n improvements
void AcademicBuilding::improve(int n){
	//Check to make sure the owner has a monopoly
	//If the owner can sucessfully pay for the improvements
	//Assume owner has enough to pay for improvement
	numImprov++;
	game->notifyImprove(index,n);
	game->refreshBoard();

}


//Assume the player calling this can sell the improvement
void AcademicBuilding::sellImprove(int n){
	numImprov-=n;
	game->notifyImprove(index,-n);
	game->refreshBoard();
}

int AcademicBuilding::getImprCost(){
	return imprCost;
}

void AcademicBuilding::setImprove(int improv){
	numImprov += improv;
}

void AcademicBuilding::doAction(Player* p){
	int tuit = tuition[numImprov];

	if (owner->getName()!= "BANK" && static_cast<Player*>(owner)->getSymbol()!=p->getSymbol()){
		if (mortgaged){
			cout<<"You were not charged for landing on "<<name<<" because it is currently mortgaged."<<endl;

		}else{

			if (static_cast<Player*>(owner)->hasMonopoly(block) && numImprov == 0)
				tuit =2*tuit;
			cout<<"You will be charged $"<<tuit<<" in tuition by "<<owner->getName()<<", the owner of "<<name<<"."<<endl;
			cout<<"Please give "<<owner->getName()<<" a few seconds to collect the tuition..";
			cout.flush();
			usleep(500000);
			cout<<".";
			cout.flush();
			usleep(500000);
			cout<<".";
			cout.flush();
			usleep(500000);
			cout<<"."<<endl;


			if (p->pay(tuit, owner)){
				cout<<"Now you have $" <<p->getCash()<<" in cash."<<endl;
			}
		}
	}
}

int AcademicBuilding::getValue(){
	return (cost + numImprov*imprCost);
}

