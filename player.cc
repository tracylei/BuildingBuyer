#include "player.h"
#include "bank.h"
#include "academicbuilding.h"
#include "controller.h"
#include <unistd.h>

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
	for(vector<Property*>::iterator it = properties.begin(); it != properties.end(); ++it){
		delete(*it);
	}
	properties.clear();
	cout << "player destructor" << endl;	
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
	int index=-1;
	for (int i=0; i<size; i++){
		if(properties.at(i)->getBlock() == p->getBlock()){
			properties.erase(properties.begin()+index);
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
		cout << "You do not have enough cash to do that!" << endl;
		//INCOMPLETE add in bankruptcy
		cout<<"You need to pay $"<<amt<<" but you only have $"<<cash<<". Would you like to attempt a trade,"; 
		cout<<" mortgage buildings, sell improvements, or declare bankruptcy?"	<<endl;
		cout<<endl;
		cout<<"Your assets consists of:"<<endl;
		displayAssets();
		cout<<endl;
		string cmd, input;
		getline(cin, input);
		istringstream iss(input);
		iss>>cmd;
		string propName, cmd2;
		Property* p;
		while(cmd!="bankrupt"){
			istringstream iss2(input);
			iss2>>cmd;
			cout<<"cmd: "<<cmd<<endl;
			iss2>>propName;
			cout<<"prop: "<<propName<<endl;
			p = owns(propName);
			if (cmd=="improve"){
				iss2>>cmd2;
				cout<<"cmd2: "<<cmd2<<endl;
				if (cmd2=="buy"){
					cout<<"You must deal with your debt (ex. by selling improvements, not buying) before issuing any other commands."<<endl;
					cout<<"Please issue a valid \"improve\", \"mortgage\", and \"bankrupt\" command."<<endl;
				}else if(!p){
					cout<<"You can only buy/sell improvements on properties that you own."<<endl;
					cout<<"Please issue a valid \"improve\", \"mortgage\", and \"bankrupt\" command."<<endl;
				}else if(!p->isAcademic()){
					cout<<"Improvements can only be found on Academic Buildings."<<endl;
					cout<<"Please issue a valid \"improve\", \"mortgage\", and \"bankrupt\" command."<<endl;
				}else if(static_cast<AcademicBuilding*>(p)->getImpr()<0){
					cout<<"There are no improvements on "<<propName<<"for you to sell."<<endl;
					cout<<"Please issue a valid \"improve\", \"mortgage\", and \"bankrupt\" command."<<endl;
				}
					else break;
			}else if (cmd=="mortgage"){
				iss2>>propName;
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
			istringstream iss(input);
			iss>>cmd;
		}

		if (cmd=="bankrupt"){
			declareBankruptcy(creditor);
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
	return false;
}


void Player::declareBankruptcy(Owner* creditor){
	cout<<"You've declared bankruptcy."<<endl;
	cout<<"All of your assets will now be transferred to "<<creditor->getName()<<".";
	cout.flush();
	creditor->claimAssets(this);
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
	cout<<"."<<endl;
	usleep(700000);
	game->endTurn();
	game->removePlayer(this);
	if (game->isWon()){
		cout<<"Congratulations "<<creditor->getName()<<"! You've won the game."<<endl;
		game->clearGame();
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
			cout<<name<<", the ownership of "<<(**it).getName()<<" has been transferred to you from "<<debtor->getName();
			cout<<" because "<<debtor->getName()<<" owes you money and has declared bankruptcy."<<endl;
			cout<<"Since this is a mortgaged property, you must immediately pay 10% of the cost to the Bank."<<endl;
			cout<<"Please allow the bank some time to collect the $"<<.1*(**it).getCost()<<" in fees."<<endl;
			usleep(1000000);
			cout<<"3..."<<endl;
			usleep(1000000);
			cout<<"2.."<<endl;
			usleep(1000000);
			cout<<"1."<<endl;
			usleep(1000000);
			if (pay(.1*(**it).getCost(),game->getBank())){
				cout<<"You now have "<<cash<<" left in cash."<<endl;
			

				cout<<"Would you like to unmortgage "<<(**it).getName()<<" right now by paying the principle of "<<(**it).getCost()<<"? (y/n)"<<endl;
				cout<<"Please note that if you do not unmortgage "<<(**it).getName()<<" now, you will be charged the additional 10% unmortgage fee later."<<endl; 
				string cmd;
				getline(cin,cmd);
				while (cmd!="y" && cmd!="n"){
					cout<<"Please only use \"y\" and \"n\" to indicate your decision."<<endl;
					getline(cin, cmd);
				}
				if (cmd=="y"){
					unmortgage(*it, 1);
				}
			}
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
	// move(jailRoll1, jailRoll2);
	// game->refreshBoard();
	cout<<"Congratulations on leaving the Tim's line." << endl;
	// cout<<"Congratulations on leaving the Tim's line. Based on the sum of your dice rolls from your last attempt to leave, you moved ";
	// cout<<jailRoll1+jailRoll2<<" cells."<<endl;
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
void Player::unmortgage(Property *p, double feeRate){
	if (!p){
		cout<<"Sorry, you can only unmortgage properties that you own."<<endl;
	}else if (!p->isMortgaged()){
		cout<<p->getName()<<" hasn't been mortgaged yet."<<endl;
	}else{
		int amt = p->getCost() * feeRate;
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

