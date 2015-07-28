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
#if DEBUG
	cout << symbol << curPosition << " " <<cash << endl;
#endif
};

Player::~Player(){
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

void Player::setJailRolls(int roll1, int roll2){
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
		//INCOMPLETE add in bankruptcy
		cout<<"You need to pay $"<<amt<<" but you only have $"<<cash<<". Would you like to attempt a trade,"; 
		cout<<"mortgage buildings, sell improvements, or declare bankruptcy?"	<<endl;
		string cmd, input;
		getline(cin, input);
		istringstream iss(input);
		iss>>cmd;
		string propName, cmd2;
		Property* p;
		while(cmd!="bankrupt"){
			iss>>propName;
			p = owns(propName);
			if (cmd=="improve"){
				iss>>cmd2;
				if (cmd2!="buy"){
					cout<<"You must deal with your debt (ex. by selling improvements, not buying) before issuing any other commands."<<endl;
					cout<<"Please issue a valid \"improve\", \"mortgage\", and \"bankrupt\" command."<<endl;
				}else if(!p){
					cout<<"You can only buy/sell improvements on properties that you own."<<endl;
					cout<<"Please issue a valid \"improve\", \"mortgage\", and \"bankrupt\" command."<<endl;
				}else if(!p->isAcademic()){
					cout<<"Improvements can only found on Academic Buildings."<<endl;
					cout<<"Please issue a valid \"improve\", \"mortgage\", and \"bankrupt\" command."<<endl;
				}else if(static_cast<AcademicBuilding*>(p)->getImpr()<0){
					cout<<"There are no improvements on "<<propName<<"for you to sell."<<endl;
					cout<<"Please issue a valid \"improve\", \"mortgage\", and \"bankrupt\" command."<<endl;
				}
					else break;
			}else if (cmd=="mortgage"){
				iss>>propName;
				if(!p){
					cout<<"You can only mortgage properties that you own."<<endl;
					cout<<"Please issue a valid \"improve\", \"mortgage\", and \"bankrupt\" command."<<endl;
				}
				else break;
			}else if (cmd!="improve"&&cmd!="mortgage"){
				cout<<"You must deal with your debt before issuing any other commands."<<endl;
				cout<<"Please only use the \"improve\", \"mortgage\", and \"bankrupt\" commands."<<endl;
			}
			getline(cin, input);
		}

		if (cmd=="bankrupt"){
			cout<<"declare bankruptcy"<<endl;
		//	declareBankruptcy(creditor);
			return false;
		}else if (cmd=="improve"){
			sellImprove(static_cast<AcademicBuilding*>(p));
			return pay (amt, creditor);
		}else if(cmd=="mortgage"){
			mortgage(p);
			return pay (amt, creditor);
		}
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
	cout<<"Congratulations on leaving the Tim's line.";
	inJail = false;
	turnsInJail = 0;
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
		cout<<"Sorry, "<<p->getName()<<"has already been mortgaged."<<endl;
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
	}
	else if (p->getImpr()>5){
			cout<<"Sorry, you can only have a maximum of 5 improvements on each improvable property."<<endl;
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

