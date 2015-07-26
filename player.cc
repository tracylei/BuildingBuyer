#include "player.h"
#include "controller.h"

using namespace std;

// Player::Player(): Owner(1500),game(NULL){}
// Player(char symbol, string name, int cash=1500, Properties* properties):symbol(symbol), name(name), cash(cash), properties(properties){}
Player::Player(Game* game, string name, char symbol, int curPosition, int cash, int timCups): Owner(cash), game(game), name(name), symbol(symbol), curPosition(curPosition)
, timCups(timCups){
	turnsInJail = 0;
	jailRoll1 = 0;
	jailRoll2 = 0;
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

void Player::setJailRolls(int roll1, int roll2){
	jailRoll1 = roll1;
	jailRoll2 = roll2;
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





void Player::addCash(int x){
	cash += x;
}

void Player::addProperty(Property *p){
	for (vector<Property*>::iterator it = properties.begin(); it != properties.end(); it++){
		if ((**it).getName() == p->getName()) return;
	}
	properties.push_back(p);
	cout << p->getName() << " added to player " << name << endl;
}


bool Player::pay(int amt, Owner* creditor){
	if (amt > cash) {
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
	move(jailRoll1, jailRoll2);
	game->refreshBoard();
	cout<<"Congratulations on leaving the Tim's line. Based on the sum of your dice rolls from your last attempt to leave, you moved ";
	cout<<jailRoll1+jailRoll2<<" cells."<<endl;
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
	

// bool Player::acceptTrade(Player *p, string give, string want){
// 	int amount;
// 	Property *prop;

// 	if (istringstream(give) >> amount){ //trade money for property
// 		if(amount > cash) {
// 			cout << "Not enough cash to process trade" << endl;
// 			return 0;
// 		}

// 		//find property (want) from player p
// 		for (vector<Property*>::iterator it = p->getProperties().begin(); it != p->getProperties().end(); it++){
// 			if((**it).getName() == want && (**it).getImpr() == 0) {prop = *it;}
// 			else {
// 				cout << "Trade Failed. Property has improvements" << endl;
// 				return 0;
// 			}
// 		}

// 		cash -= amount;
// 		this->properties.push_back(prop);
// 		p->properties.erase(prop);

// 	}else if (istringstream(want) >> amount){ //trade property for money
// 		if(amount > p->getCash()) {
// 			cout << "Not enough cash to process trade" << endl;
// 			return 0;
// 		}

// 		//find property (give) from this player 
// 		for (vector<Property*>::iterator it = this->getProperties().begin(); it != this->getProperties().end(); it++){
// 			if((**it).getName() == give && (**it).getImpr() == 0) {prop = *it;}
// 			else{
// 				cout << "Trade Failed. Property has improvements" << endl;
// 				return 0;
// 			}
// 		}

// 		p->properties.push_back(prop);
// 		this->properties.erase(prop);
// 		cash += amount;
// 	}else{ //trade property for property
// 		Property* propGive, propWant;

// 		for (vector<Property*>::iterator it = p->getProperties().begin(); it != p->getProperties().end(); it++){
// 			if((**it).getName() == want && (**it).getImpr() == 0) {prop = *it;}
// 			else {
// 				cout << "Trade Failed. Property has improvements" << endl;
// 				return 0;
// 			}
// 		}

// 		for (vector<Property*>::iterator it = this->getProperties().begin(); it != this->getProperties().end(); it++){
// 			if((**it).getName() == give && (**it).getImpr() == 0) {prop = *it;}
// 				cout << "Trade Failed. Property has improvements" << endl;
// 				return 0;
// 			}
// 		}

// 		p->properties.push_back(propGive);
// 		this->properties.erase(propWant);

// 		this->properties.push_back(propWant);
// 		p->properties.erase(propGive);
// 		return 1;
// 	}
// }

// bool Player::trade(Player* p, string give, string want){

// 	cout << p->getName() << " wants to trade " + give + " for " + want;

// 	while(true){
// 		string response;

// 		cout << "Accept the trade? (y/n)" << endl;
// 		cin >> response;

// 		if (response == "y"){
// 			acceptTrade(p, give, want);
// 			cout << "Trade completed." << endl;
// 			return true;
// 		}else if (response == "n"){
// 			cout << p->getName() + " has rejected your trade." << endl;
// 			return false;
// 		}else{
// 			cout << "Answer only y or n" << endl;
// 		}
// 	}
// }


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






