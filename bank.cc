#include "bank.h"
#include <vector>
using namespace std;

Bank::Bank(Game* game): Owner(0), game(game){}

string Bank::getName(){
	return "BANK";
}

void Bank::claimAssets(Player* debtor){
	vector<Property*> properties = debtor->getProperties();
	for (vector<Property*>::iterator it = properties.begin(); it != properties.end(); it++){
		(**it).setOwner(this);
		(**it).setMortgaged(false);
	}
	game->reclaimTimCups(debtor->getTimCups());
}


