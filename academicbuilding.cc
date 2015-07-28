#include <iostream>
#include "academicbuilding.h"
#include <unistd.h>

AcademicBuilding::AcademicBuilding(std::string name, int cost, std::string block, int improvCost):
								Property(name, block, cost, true),imprCost(improvCost){
	tuition = new int [MAX_IMPROVEMENTS+1];
	// for (int i = 0; i <= MAX_IMPROVEMENTS; i++){
	// 		cout << tuition[i] << " ";
	// }

}

AcademicBuilding::~AcademicBuilding(){
	delete [] tuition;
}

void AcademicBuilding::setTuition(int index, int tutCost){
	tuition[index] = tutCost;
}
// Build n improvements
void AcademicBuilding::improve(int n){
	//Check to make sure the owner has a monopoly
	//If the owner can sucessfully pay for the improvements
	if (static_cast<Player*>(owner)->pay(n*imprCost, game->getBank())){
		numImprov++;
		game->notifyImprove(index,n);
		game->refreshBoard();
	}
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
	if (static_cast<Player*>(owner)->hasMonopoly(block) && numImprov == 0)
		tuit *=2;
	if (owner->getName()!= "bank" && owner->getName()!=p->getName() && !mortgaged){
		cout<<"You will be charged $"<<tuit<<" in tuition by "<<owner->getName()<<", the owner of "<<name<<"."<<endl;
		cout<<"Please give "<<owner->getName()<<" a few seconds to collect the tuition..";
		cout.flush();
		usleep(1000000);
		cout<<".";
		cout.flush();
		usleep(1000000);
		cout<<"."<<endl;
		cout.flush();
		usleep(1000000);

		cout<<"You had $"<<p->getCash()<<" before paying, ";
		if (p->pay(tuit, owner))
			cout<<"now you have $" <<p->getCash()<<"."<<endl;
	}
}

int AcademicBuilding::getValue(){
	return (cost + numImprov*imprCost);
}

