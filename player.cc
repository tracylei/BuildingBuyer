#include "player.h"
#include "academicbuilding.h"
#include "controller.h"

using namespace std;

// Player::Player(): Owner(1500),game(NULL){}
// Player(char symbol, string name, int cash=1500, Properties* properties):symbol(symbol), name(name), cash(cash), properties(properties){}
Player::Player(Game* game, string name, char symbol, int curPosition, int cash, int timCups): Owner(cash), game(game), name(name), symbol(symbol), curPosition(curPosition)
, timCups(timCups){
	inJail = false;
	turnsInJail = 0;
	jailRoll1 = 0;
	jailRoll2 = 0;
#if DEBUG
	cout << symbol << curPosition << " " <<cash << endl;
#endif
};

Player::~Player(){
	for(vector<Property*>::iterator it = properties.begin(); it != properties.end(); ++it){
		delete(*it);
	}
	properties.clear();
	delete game;
}

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

void Player::setJailRolls(int roll1, int roll2){
	jailRoll1 = roll1;
	jailRoll2 = roll2;
	turnsInJail++;
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
	cout << p->getName() << " added to player " << name <<"'s list of properties owned."<< endl;
}

void Player::removeProperty(Property* p){
	int size = monopolies.size();
	int index=-1;
	for (int i=0; i<size; i++){
		if(monopolies.at(i) == p->getBlock()){
			index = i;
		}
	}
	if (index>=0)
		monopolies.erase(monopolies.begin()+index);
	removeMonopoly(p->getBlock());
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
		cout << "You do not have enough cash to do that!" << endl;
		//INCOMPLETE add in bankruptcy
		// cout<<"You are short $"<<amt-cash<<". Would you like to attempt a trade, 
		// mortgage buildings, sell ipmrovements, or declare bankruptcy?"	<<endl;
		// string cmd;
		// cin>>cmd;
		// if (cmd=="bankrupt")
		return false;
	}
	else {
		cash-=amt;
		creditor->addCash(amt);
		return true;
	}
}

void Player::goToJail(){
	game->notify(this, curPosition, 10); 
	curPosition = 10;
	inJail = true;
	turnsInJail = 0;
}

void Player::leaveJail(){
	// move(jailRoll1, jailRoll2);
	// game->refreshBoard();
	cout<<"Congratulations on leaving the Tim's line." << endl;
	// cout<<"Congratulations on leaving the Tim's line. Based on the sum of your dice rolls from your last attempt to leave, you moved ";
	// cout<<jailRoll1+jailRoll2<<" cells."<<endl;
	inJail = false;
}

bool Player::isInJail(){
	return inJail;
}


void Player::move(int r1, int r2){
	int prevPosition = curPosition;
	if ((curPosition + r1 + r2)<=39)
		curPosition += r1 + r2;
	else
		curPosition = (curPosition + r1 + r2) % 39 - 1;
	game->notify(this, prevPosition, curPosition); 
	game->refreshBoard();
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
	game->notifyCell(curPosition);
}


void Player::displayAssets(){
	cout << "Player " << name << "'s assets." <<endl;
	cout << "Cash: " << cash << endl;
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
			cout << "Not enough cash to process trade" << endl;
			return 0;
		}
		// cout << "cur:" << this->getName() << " trading " << pl->getName() << pl->getPos()<< endl;
		//find property (want) from player p


		for (unsigned int n = 0; n < pl->getProperties().size(); ++n){

			prop = pl->getProperties().at(n);

			if(prop->getName() == want && prop->getImpr() == 0){
				cash -= amount;
				addProperty(prop);
				pl->removeProperty(prop);
				cout << "Trade completed." << endl;
				return 1;
			}else{
				cout << "Trade Failed. Property has improvements." << endl;
				return 0;
			}
		}

	}else if (istringstream(want) >> amount){ //trade property for money
		if(amount > pl->getCash()) {
			cout << "Not enough cash to process trade." << endl;
			return 0;
		}

		for (unsigned int n = 0; n < getProperties().size(); ++n){

			prop = getProperties().at(n);

			if(prop->getName() == give && prop->getImpr() == 0){
				cash += amount;
				pl->addProperty(prop);
				removeProperty(prop);
				cout << "Trade completed." << endl;
				return 1;
			}else{
				cout << "Trade Failed. Property has improvements." << endl;
				return 0;
			}
		}
	}else{ //trade property for property
		Property* propGive;
		Property* propWant;

		for (unsigned int n = 0; n < pl->getProperties().size(); ++n){

			propWant = pl->getProperties().at(n);

			if(propWant->getName() == want && propWant->getImpr() == 0){
				cash -= amount;
				addProperty(propWant);
				pl->removeProperty(propWant);

			}else{
				cout << "Trade Failed. Property has improvements." << endl;
				return 0;
			}
		}

		for (unsigned int n = 0; n < getProperties().size(); ++n){

			propGive = getProperties().at(n);

			if(propGive->getName() == give && propGive->getImpr() == 0){
				cash += amount;
				pl->properties.push_back(propGive);
				erase(propGive);

			}else{
				cout << "Trade Failed. Property has improvements." << endl;
				return 0;
			}
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

		cout << "Accept the trade? (y/n)" << endl;
		cin >> response;

		if (response == "y"){
			acceptTrade(pl, give, want);
			break;
		}else if (response == "n"){
			cout << pl->getName() + " has rejected your trade." << endl;
			break;
		}else{
			cout << "Answer only y or n" << endl;
		}
	}
}

void Player::mortgage(Property *p){
	if (!p->isMortgaged() && p->getImpr() == 0 && p->getOwner()->getName() == name){
		p->setMortgaged(true);
		cash += p->getCost() / 2;
		cout << p->getName() << " has been mortgaged!" << endl;
	}else{
		cout << "This property cannot be mortgaged!" << endl;
	}
}

void Player::unmortgage(Property *p){
	if (p->isMortgaged() && p->getOwner()->getName() == name){//&& p->owner.name? == player.name
		int amt = p->getCost() * 1.1;
		if(amt > cash){
			cout << "Not enough fund to unmortgage this property!" << endl;
		}else{
			p->setMortgaged(false);
			cash -= amt;
			cout << p->getName() << " has been unmortgaged!" << endl;
		}
	}
}






