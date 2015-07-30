#include "player.h"
#include "bank.h"
#include "academicbuilding.h"
#include "controller.h"
#include <unistd.h>

using namespace std;

Player::Player(Game* game, string name, char symbol, int curPosition, int cash, int timCups): Owner(cash), game(game), name(name), symbol(symbol), curPosition(curPosition)
, timCups(timCups){
	inJail = false;
	turnsInJail = 0;
#if DEBUG
	cout << symbol << curPosition << " " <<cash << endl;
#endif
};

string Player::getName(){
	return name;
}

char Player::getSymbol(){
	return symbol;
}

int Player::getCash(){
	return cash;
}

int Player::getPos(){
	return curPosition;
}

int Player::getTimCups(){
	return timCups;
}

void Player::useTimCup(){
	timCups--;
}

void Player::incrTimCups(){
	timCups++;
}

int Player::getTurnsInJail(){
	return turnsInJail;
}

void Player::incrTurnsInJail(){
	turnsInJail++;
}

vector<Property*> Player::getProperties(){
	return properties;
}

int Player::getNumRezOwned(){
	int rezOwned = 0;
	for (vector<Property*>::iterator it = properties.begin(); it != properties.end(); it++){
		if ((**it).getName() == "MKV" || (**it).getName() == "REV" || 
			(**it).getName() == "V1" || (**it).getName() == "UWP") 
			rezOwned++;
	}
	return rezOwned;
}

int Player::getNetWorth(){
	int worth = cash;
	for (vector<Property*>::iterator it = properties.begin(); it != properties.end(); it++){
		worth += (**it).getValue();
	}
	return worth;
}


int Player::getCurPos(){
	return curPosition;
}


void Player::setJail(bool v, int turns){
	inJail = v;
	turnsInJail = turns;
}

void Player::addCash(int x){
	cash += x;
}

void Player::addProperty(Property *p){
	for (vector<Property*>::iterator it = properties.begin(); it != properties.end(); it++){
		if ((**it).getName() == p->getName()) return;
	}
	p->setOwner(this);
	properties.push_back(p);
	addMonopoly(p->getBlock());
	cout << p->getName() << " added to " << name <<"'s list of properties owned."<< endl;
}

void Player::removeProperty(Property* p){
	int size = properties.size();
	for (int i=0; i<size; i++){
		if(properties.at(i)->getName() == p->getName()){
			properties.erase(properties.begin()+i);
			removeMonopoly(p->getBlock());
			return;
		}
	}

}
void Player::addMonopoly(string block){
	for (int i = 0; i<40; i++){
		Cell* c = game->getTheGrid(i);
		if (c->isAcademic()){
			AcademicBuilding* ab = static_cast<AcademicBuilding*>(c);
			if(ab->getBlock()==block &&
				ab->getOwnerName()!= game->getCurrentPlayer()->getName()){
				return;
			}
		}
	}
	monopolies.push_back(block);
}

void Player::removeMonopoly(string block){
	int size = monopolies.size();
	for (int i=0; i<size; i++){
		if(monopolies.at(i) == block){
			monopolies.erase(monopolies.begin()+i);
			return;
		}
	}
}

bool Player::hasMonopoly(string block){
	int size = monopolies.size();
	for (int i=0; i<size; i++){
		if(monopolies.at(i) == block){
			return true;
		}
	}
	return false;
}



bool Player::pay(int amt, Owner* creditor){
	if (amt > cash) {
		cout<<endl;
		cout << "You do not have enough cash!" << endl;
		//INCOMPLETE add in bankruptcy
		cout<<"You need to pay $"<<amt<<" but you only have $"<<cash<<". Would you like to attempt a trade,"; 
		cout<<" mortgage buildings, sell improvements, or declare bankruptcy?"	<<endl;
		cout<<endl;
		cout<<"Your assets consists of:"<<endl;
		displayAssets();
		game->notifyControllerBankrupt(this, creditor, amt);
	}
	else {
		cash-=amt;
		cout<<name<<", you've successfully paid "<<creditor->getName()<<" $"<<amt<<"."<<endl;
		creditor->addCash(amt);
		return true;
	}
	return 0;
}

void Player::declareBankruptcy(Owner* creditor){
	cout<<"You've declared bankruptcy."<<endl;
	if (game->getNumPlayers()==2){
		game->endGame();
	}else{
		game->removePlayer(symbol);
		cout<<"All of your assets will now be transferred to "<<creditor->getName()<<".";
		cout.flush();
		cout<<".";
		cout.flush();
		usleep(300000);
		cout<<".";
		cout.flush();
		usleep(300000);
		cout<<".";
		cout.flush();
		usleep(300000);
		cout<<".";
		cout.flush();
		usleep(400000);
		cout<<".";
		cout.flush();
		usleep(500000);
		creditor->claimAssets(this);

		game->endTurn();
		delete this;
	}
}


void Player::claimAssets(Player* debtor){
	vector<Property*> props = debtor->getProperties();
	timCups+=debtor->getTimCups();
	cash+=debtor->getCash();
	for (vector<Property*>::iterator it = props.begin(); it != props.end(); it++){
		(**it).setOwner(this);
		addProperty(*it);
		if((**it).isMortgaged()){
				getMortgagedProp(*it, 1, 1.1);
		}
	}
}

//this player is getting a mortgaged property
void Player::getMortgagedProp(Property* p, double yFee, double nFee){
		cout<<name<<", the ownership of "<<p->getName()<<" has been transferred to you.";
		cout<<"Since this is a mortgaged property, you must immediately pay 10% of the cost to the Bank."<<endl;
		cout<<"Please allow the bank some time to collect the $"<<.1*p->getCost()<<" in fees."<<endl;
		usleep(1000000);
		cout<<"3..."<<endl;
		usleep(1000000);
		cout<<"2.."<<endl;
		usleep(1000000);
		cout<<"1."<<endl;
		usleep(1000000);
		if (pay(.1*p->getCost(),game->getBank())){
			cout<<"You now have $"<<cash<<" left in cash."<<endl;
		

		cout<<"Would you like to unmortgage "<<p->getName()<<" right now by paying the principle of "<<p->getCost()<<"? (y/n)"<<endl;
		cout<<"Please note that if you do not unmortgage "<<p->getName()<<" now, you will be charged the additional 10% unmortgage fee later."<<endl; 
		string cmd;
		getline(cin,cmd);
		while (cmd!="y" && cmd!="n"){
			cout<<"Please only use \"y\" and \"n\" to indicate your decision."<<endl;
			getline(cin, cmd);
		}
		if (cmd=="y"){
			p->setFeeRate(yFee);
			unmortgage(p);
		}else{
			p->setFeeRate(nFee);
		}
	}
}

void Player::goToJail(){
	game->notify(this, curPosition, 10); 
	curPosition = 10;
	inJail = true;
	turnsInJail = 0;
}

void Player::leaveJail(){

	cout<<"Congratulations on leaving the Tim's line." << endl;
	inJail = false;
	turnsInJail = 0;
}

bool Player::isInJail(){
	return inJail;
}


void Player::move(int r1, int r2){
	int prevPosition = curPosition;
	if ((curPosition + r1 + r2)<=39){
		curPosition += r1 + r2;
	}else{
		curPosition = (curPosition + r1 + r2); 
		if(curPosition > 39){
			if (!inJail){
				cout << "You've just received an OSAP grant of $200" << endl;
				cash += 200;
			}
			curPosition = curPosition % 39 - 1;	
		}
	}

	game->notify(this, prevPosition, curPosition); 
	game->refreshBoard();
	if (prevPosition>curPosition){
		cout<<"Congratulations on passing COLLECT OSAP! You've been rewarded with $200."<<endl;
		cash+=200;
	}
	cout<<"You rolled a "<<r1<<" and a "<<r2<<"."<<endl;
	game->notifyCell(curPosition);
}

void Player::slcMove (int move){
	int prevPosition = curPosition;
	if (move > -3){
		curPosition += move;
	}
	else{
		curPosition = 39;
	}
	game->notify(this, prevPosition, curPosition); 
	game->refreshBoard();
	if (prevPosition>curPosition){
		cout<<"Congratulations on passing COLLECT OSAP! You've been rewarded with $200."<<endl;
		cash+=200;
	}
	game->notifyCell(curPosition);
}


void Player::displayAssets(){
	cout << "Cash: " << cash << endl;
	cout <<"Roll Up the Rim Cups: "<<timCups<<endl;
	cout << "Properties: "; 

	for(vector<Property*>::iterator it = properties.begin(); it != properties.end(); it++){
		cout << (**it).getName() << " ";
	} 	
	cout << endl;
}
	
void Player::erase(Property *p){
	for (vector<Property*>::iterator it = this->properties.begin(); it != this->properties.end(); it++){

			if((**it).getName() == p->getName()) {
				it = properties.erase(it);
				break;
			}
	}
}

bool Player::acceptTrade(Player *pl, string give, string want){
	int amount;
	Property *prop;

	if (istringstream(give) >> amount){ //trade money for property
		if(amount > cash) {
			cout << name<<", you do not have enough cash to process the trade." << endl;
			return 0;
		}
		// cout << "cur:" << this->getName() << " trading " << pl->getName() << pl->getPos()<< endl;
		//find property (want) from player p

		prop = pl->owns(want);

		if(prop && prop->getImpr() == 0){
			cash -= amount;
			addProperty(prop);
			if (prop->isMortgaged()){
				getMortgagedProp(prop,0.5,0.6);
			}
			pl->removeProperty(prop);
			cout << "Trade completed." << endl;
			return 1;
		}else{
			cout << "Trade failed. Property has improvements." << endl;
			return 0;
		}


	}else if (istringstream(want) >> amount){ //trade property for money
		if(amount > pl->getCash()) {
			cout << "Not enough cash to process trade." << endl;
			return 0;
		}
			prop = owns(give);

			if(prop && prop->getImpr() == 0){
				cash += amount;
				pl->addProperty(prop);
				if (prop->isMortgaged()){
					cout<<"mortgaged"<<endl;
					pl->getMortgagedProp(prop,0.5,0.6);
				}
				removeProperty(prop);
				cout << "Trade completed." << endl;
				return 1;
			}else{
				cout << "Trade failed. Property has improvements." << endl;
				return 0;
			}

	}else{ //trade property for property

		Property* propWant = pl->owns(want);
		Property* propGive = owns(give);
			if(propWant && propWant->getImpr() == 0 &&
				propGive && propGive->getImpr() == 0){

				if (propWant->isMortgaged()){
					getMortgagedProp(propWant,0.5,0.6);
				}
				addProperty(propWant);
				pl->removeProperty(propWant);
				if (propGive->isMortgaged()){
					pl->getMortgagedProp(propGive,0.5,0.6);
				}
				pl->addProperty(propGive);
				removeProperty(propGive);

			}else{
				cout << "Trade Failed. Property has improvements." << endl;
				return 0;
			}
			cout << "Trade completed." << endl;
			return 1;
	}
	return 0;
}

void Player::trade(Player* pl, string give, string want){

	cout << getName() << " wants to trade " << pl->getName() << " " + give + " for " + want<<".";

	while(true){
		string response;

		cout << " Accept the trade? (y/n)" << endl;
		getline(cin,response);


		if (response == "y"){
			acceptTrade(pl, give, want);
			break;
		}else if (response == "n"){
			cout << pl->getName() + " has rejected your trade." << endl;
			break;
		}else
			cout<<"Please only answer with \"y\" or \"n\"."<<endl;
	}
}

//Already know that the player owns p
void Player::mortgage(Property *p){
	if (!p){
		cout<<"Sorry, you can only mortgage properties that you own."<<endl;
	}
	else if (p->isMortgaged()){
		cout<<"Sorry, "<<p->getName()<<" has already been mortgaged."<<endl;
	} else if(p->getImpr() != 0){
		cout<<"Sorry, you can only mortgage properties with no improvements."<<endl;
	}
	else{	
		p->setMortgaged(true);
		cash += p->getCost() / 2;
		cout << p->getName() << " has been mortgaged!" << endl;
	}
}

//Already know that the player owns p
void Player::unmortgage(Property *p){
	if (!p){
		cout<<"Sorry, you can only unmortgage properties that you own."<<endl;
	}else if (!p->isMortgaged()){
		cout<<p->getName()<<" hasn't been mortgaged yet."<<endl;
	}else{
		int amt = p->getCost() * p->getFeeRate();
		if(amt > cash){
			cout << "Not enough fund to unmortgage this property!" << endl;
		}else{
			p->setMortgaged(false);
			cash -= amt;
			cout << p->getName() << " has been unmortgaged for $" << amt<<" at a rate of "<<p->getFeeRate()<<" times the purchase price!"<< endl;
		}
	}
}


Property* Player::owns(string propName){
	//Check that the current player actually owns the property
			int numProp = properties.size();
			
			for (unsigned int i = 0; i < numProp; i++){
				if (properties[i]->getName() == propName){
					return properties[i];
				}
			}
			return NULL;
}

void Player::buyImprove(AcademicBuilding* p){
	bool monopoly = hasMonopoly(p->getBlock());
	if (!monopoly){
		cout<<"Sorry, you can only purchase improvements on a property when you own all properties in its block."<<endl;
	}else if (monopoly){
		if (pay(p->getImprCost(), game->getBank())){
			p->improve(1);
			cout<<"You've successfully purchased an improvement for "<<p->getName()<<" for $";
			cout<<p->getImprCost()<<"."<<endl;
		}
	
		else if (p->getImpr()>5){
				cout<<"Sorry, you can only have a maximum of 5 improvements on each improvable property."<<endl;
		}
	}
}


void Player::sellImprove(AcademicBuilding* p){
	if (p->getImpr()<=0){
		cout<<"Sorry, there are no improvements on "<<p->getName()<<" for you to sell."<<endl;
	}
	else{
		p->sellImprove(1);
		int price = p->getImprCost()/2;
		cash+=price;
		cout<<"You've successfully sold an improvement for "<<p->getName()<<" for $";
		cout<<price<<"."<<endl;
	}
}
