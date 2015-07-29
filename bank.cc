#include "bank.h"
#include <vector>
using namespace std;

Bank::Bank(Game* game): Owner(0), game(game){}

Bank::~Bank(){
	delete game;
}

string Bank::getName(){
	return "BANK";
}

void Bank::claimAssets(Player* debtor){
	vector<Property*> properties = debtor->getProperties();
	for (vector<Property*>::iterator it = properties.begin(); it != properties.end(); it++){
		(**it).setOwner(this);
		//Debtor is still in the game at this point
		if ((**it).isMortgaged()){
			cout<<"The mortgaged property, "<<(**it).getName()<<" has been returned to the bank."<<endl;
			cout<<"The bank will now auction it."<<endl;
			(**it).auction(game->getNumPlayers(),game->getPlayers(), debtor->getName());
			(**it).setMortgaged(false);
		}
	}
	game->reclaimTimCups(debtor->getTimCups());
}


