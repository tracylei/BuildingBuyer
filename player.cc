#include "player.h"
#include "controller.h"

using namespace std;

Player::Player(): Owner(1500),game(NULL){}
// Player(char symbol, string name, int cash=1500, Properties* properties):symbol(symbol), name(name), cash(cash), properties(properties){}
Player::Player(Game* game, string name, char symbol, int curPosition, int cash, int timCups): Owner(cash), game(game), name(name), symbol(symbol), curPosition(curPosition)
, timCups(timCups){
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

vector<Property*> Player::getProperties(){
	return properties;
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


bool Player::pay(int amt, Player* creditor){
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
	curPosition = 10;
	inJail = true;
}

void Player::move(){
	int prevPosition = curPosition;
	curPosition = (curPosition + game->rollDice()) % 39;
	//notify board of move
	game->notify(this, prevPosition, curPosition); 
}

void Player::move(int r1, int r2){
	int prevPosition = curPosition;
	curPosition = (curPosition + r1 + r2) % 39;
	game->notify(this, prevPosition, curPosition); 
}

void Player::displayAssets(){
	cout << "Player " << name << "'s' assets." <<endl;
	cout << "Cash: " << cash << endl;
	cout << "Properties: ";

	for(vector<Property*>::iterator it = properties.begin(); it != properties.end(); it++){
		cout << (**it).getName() << " ";
	} 	
}

// bool Player::acceptTrade(Player *p, string give, string want){
// 	int amout;
// 	Property *prop;

// 	if (istringstream(give) >> amount){ //trade money for property
// 		if(amount > cash) {
// 			cout << "Not enough cash to process trade" << endl;
// 			return 0;
// 		}

// 		//find property (want) from player p
// 		for (vector<Properties*> iterator it = p->getProperties().begin(); it != p->getProperties().end(); it++){
// 			if(it->getName() == want && it->getImpr() == 0) {prop = it;}
// 			else {
// 				cout << "Trade Failed. Property has improvements" << endl;
// 				return 0;
// 			}
// 		}

// 		cash -= amount;
// 		this->properties.push_back(prop);
// 		p->properties.erase(prop);

// 	}else if (istringstream(want) >> amount){ //trade property for money
// 		if(amount > p.getCash()) {
// 			cout << "Not enough cash to process trade" << endl;
// 			return 0;
// 		}

// 		//find property (give) from this player 
// 		for (vector<Properties*> iterator it = this->getProperties().begin(); it != this->getProperties().end(); it++){
// 			if(it->getName() == give && it->getImpr() == 0) {prop = it;}
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

// 		for (vector<Properties*> iterator it = p->getProperties().begin(); it != p->getProperties().end(); it++){
// 			if(it->getName() == want && it->getImpr() == 0) {prop = it;}
// 			else {
// 				cout << "Trade Failed. Property has improvements" << endl;
// 				return 0;
// 			}
// 		}

// 		for (vector<Properties*> iterator it = this->getProperties().begin(); it != this->getProperties().end(); it++){
// 			if(it->getName() == give && it->getImpr() == 0) {prop = it;}
// 			else{
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

// void Player::buy(Property *p){
// 	if(cash >= p->cost){
// 		cash -= p->cost;
// 		p->owner = this;
// 		properties.push_back(p);
// 	}
// }

// void Player::mortgage(Property *p){

// 	if (!p->mortgaged && p->numImpr == 0 && properties.count(p->getName()) > 1){
// 		p->mortgaged == true;
// 		player.cash += p->cost / 2;
// 	}else{
	// 	cout << "This property cannot be mortgaged!" << endl;
	// }
// }

// void Player::unmortgage(Property *p){
// 	if (p->mortgaged){//&& p->owner.name? == player.name
		
// 	}
// }

void Player::play(){


	cout << getName() << "'s turn. Please enter your commands." << endl;
	//player commands..

	bool rolled = false;

	string input;
	string cmd;
	while(getline(cin,input)){
		istringstream iss(input);
		iss >> cmd;
		if (cmd == "roll"){
			if (!rolled) {
				//DEBUG
				cout<<getName()<<" rolls the dice"<<endl;
				rolled=true;
				if(game->getTestMode()){
					int r1, r2;
					iss >> r1 >> r2;
					move(r1,r2);
				}else{
					move();
				}
				game->refreshBoard();
			}
		//What if asks to roll twice
		}else if (cmd == "next"){//end turn
			game->endTurn();

		// }else if (cmd == "trade"){
		// 	string player, give, want;
		// 	Player *p;

		// 	iss >> player >> give >> want;

		// 	//find player.
		// 	// p = game->getPlayers().find(name); //not correct syntax
		// 	trade(p, give, want);
		// }else if (cmd == "improve"){
		// 	string propName, action;
		// 	iss >> propName >> action;

		// 	if (action == "buy"){
		// 		for (vector<Property*>::iterator it = properties.begin(); it != properties.end(); it++){
		// 			if (it->getName() == propName) it->buyImprove();
		// 		}
		// 	}else if (action == "sell"){
		// 		for (vector<Property*>::iterator it = properties.begin(); it != properties.end(); it++){
		// 			if (it->getName() == propName) it->sellImprove();
		// 		}
		// 	}

		// }else if (cmd == "mortgage"){
		// 	string propName;
		// 	Property *p;
		// 	for (vector<Property*>::iterator it = properties.begin(); it != properties.end(); it++){
		// 			if (it->getName() == propName) mortgage(it);
		// 	}
		// 	// mortgage(p);
		// }else if (cmd == "unmortgage"){
		// 	string propName;
		// 	Property *p;
		// 	for (vector<Property*>::iterator it = properties.begin(); it != properties.end(); it++){
		// 		if (it->getName() == propName) unmortgage(it);
		// 	}
		}else if (cmd == "bankrupt"){
			//TODO
			cout<<"You can only declare bankruptcy when you owe someone more than you can pay."<<endl;
		}else if (cmd == "assets"){
			// displayAssets();
		}else if(cmd == "save"){
			//TODO
		}
	}
}