#include "controller.h"
#include "player.h"
#include "bank.h"

#include "cell.h"
#include "property.h"
#include "gym.h"
#include "academicbuilding.h"
#include "residence.h"
#include "nonproperty.h"

#include <fstream>
#include <string>
#include <sstream>

using namespace std;

int Game::rollUpCount = 0;

Game::Game(){
	theGrid = NULL;
	numPlayers = 0;
	currPlayer = 0;
	testMode = false;
	controller = NULL;
	rollUpCount = 0;
	bank = new Bank (this);
	die1 = new Dice;
	die2 = new Dice;
}

Game::~Game(){
	//delete the board
	for (int i = 0; i < GRID_SIZE; i++){
		delete theGrid[i];
	}
	//delete players
	for (vector<Player*>::iterator it = players.begin(); it != players.end(); it++ ){
		delete (*it);
	}
	players.clear();
	delete die1;
	delete die2;
	delete bank;
}


Bank* Game::getBank(){
	return bank;
}


Player* Game::getCurrentPlayer(){
	return players[currPlayer];
}

int Game::getNumPlayers(){
	return numPlayers;
}

Cell* Game::getTheGrid(int i){
	return theGrid[i];
}

void Game::reclaimTimCups(int n){
		rollUpCount -=n;
}

Player* Game::getPlayer(int p){
	return players[p];
}

vector<Player*> Game::getPlayers(){
	return players;
}


Player* Game::getPlayer(string s){

	for(vector<Player*>::iterator it=players.begin(); it != players.end(); ++it){
		if ((**it).getName() == s) {
			return *it;}
	}
	return NULL;
}

Property* Game::getProperty(string propName){
	for (int i = 0; i < 40; ++i){
		if(theGrid[i]->getName() == propName) return static_cast<Property*>(theGrid[i]);
	}
	return NULL;
}


bool Game::getTestMode(){
	return testMode;
} 

int Game::getTimCupCount(){
	return rollUpCount;
}

void Game::refreshBoard(){
	controller->refreshBoard();
}

void Game::endTurn(){
	currPlayer++;
	currPlayer %= numPlayers;


#if DEBUG
	cout<<"Player "<<currPlayer+1<<"'s turn is next."<<endl;
#endif

	controller->refreshBoard();
	if (!isWon()){
		#if DEBUG
		//TESTING
		cout<<"is not won"<<endl;
		#endif
		if (players[currPlayer]->isInJail())
			controller->playInJail();
		else
			controller->play(false);
	}
}


int Game::rollDie1(){
	return die1->roll();
}


int Game::rollDie2(){
	return die2->roll();
}
 
void Game::incrRollUpCount(){
	rollUpCount++;
}

int Game::getRollUpCount(){
	return rollUpCount;
}

void Game::addPlayer(Player* p){
	numPlayers++;
	players.push_back(p);
	//notify controller new player is added
#if DEBUG
	cout << "adding player" << endl;
#endif
	controller->notify(p, 0 ,0);
}

void Game::removePlayer (int symbol){
	numPlayers--;
	for (vector<Player*>::iterator i = players.begin(); i!= players.end(); i++){
		if ((**i).getSymbol() == symbol)
			players.erase(i);
	}
}


bool Game::isWon(){
	return (numPlayers == 1);
}


void Game::endGame(){
	cout<<"Congratulations, "<<players.at(0)->getName()<<", you've won the game!"<<endl;
	delete this;
}


//A Player calls this to notify the controller of its move
void Game::notify(Player* p, int prevPos, int curPos){
	controller->notify(p, prevPos, curPos);

	//notfiy theGrid[curPos] that a player has arrived
}

void Game::notifyCell(int curPos){
	Property *prop = static_cast<Property*>(theGrid[curPos]);
	if (!prop->isBuyable()) {
		prop->doAction(players[currPlayer]);
		return;
	}else{
		if(prop->getOwner()->getName() == "BANK" ){ //seg fault for non-property
			cout << "Would you like to buy " << prop->getName() << " for $" << prop->getCost() << "?(y/n)" << endl;
			cout<<"You currently have $"<<getCurrentPlayer()->getCash()<<"."<<endl;
			while(true){
				string resp;
				getline(cin, resp);

				if (resp == "y"){
					prop->buy(players[currPlayer]);
					break;
				}else if(resp == "n"){
					prop->auction(numPlayers, players, players[currPlayer]->getName()); //num players, not including current player
					break;
				}else{
					cout <<"Please only enter \"y\" for yes and \"n\" for no."<<endl;
				}
			}
		}else{
			prop->doAction(players[currPlayer]);
		}
	}
}


void Game::notifyImprove (int index, int numImprov){
	controller->notifyImprove(index,numImprov);
}


void Game::init(Controller* controller){
	
	theGrid = new Cell*[GRID_SIZE];	
	this->controller = controller;
	
	ifstream file ("property.txt");


	string s;
	int i = 0;
	while (file>>s){
		//0 is non property
		//1 is academic building
		//2 is residence
		//3 is gym
		string cellName;
		file >> cellName;

		if (s == "0"){
			NonProperty* np = new NonProperty(cellName);
			theGrid[i] = np;

		}else {	//Ownable Property
			
			//Read in purchase cost

			int purchaseCost;
			file>>purchaseCost;

			//Academic Building
			if(s == "1"){
				string block;
				file>>block;
				//Read in cost of building an improvement
				int improvCost;
				file>>improvCost;

				 //cout << cellName << " " << purchaseCost << " " << block << " " << improvCost << " "<<endl;

				//Read in tuition
				AcademicBuilding* ab = new AcademicBuilding(cellName, purchaseCost, block, improvCost);
				theGrid[i] = ab;
				for (int j = 0; j <= MAX_IMPROVEMENTS; j++){
					int tuitionCost;
					file>>tuitionCost;
					ab->setTuition(j, tuitionCost);
				}

			}else if (s == "2"){ // Residence
				Residence* r = new Residence (cellName);
				theGrid[i] = r;
				for (int j = 0; j < 4; j++){
					int rentFee;
					file>>rentFee;
					r->setRent(j, rentFee);
				}
			}else{ //Gym
				Gym* g = new Gym (cellName);
				theGrid[i] = g;
			}
			static_cast<Property*>(theGrid[i])->setOwner(bank);
		}
		theGrid[i]->setIndex(i);
		theGrid[i]->setGame(this);
		i++;
	}	
}


void Game::save(string fname){
	ofstream file (fname.c_str(), ofstream::out);
	file << numPlayers << endl;

	for(vector<Player*>::iterator it = players.begin(); it != players.end(); ++it){
		file << (**it).getName() << " " << (**it).getSymbol() << " " << (**it).getTimCups();
		file << " " << (**it).getCash() << " " << (**it).getPos();

		if((**it).getPos() == 10){
			if((**it).isInJail()){
				file << " 1 " << (**it).getTurnsInJail() << endl;
			}else{
				file << " 0 " << endl;
			}

		}else{
			file << endl;
		}

	}

	//loop through properties.
	for(int i = 0; i < GRID_SIZE; ++i){
		//ignore non properties.
		if(theGrid[i]->isBuyable()){
			file << theGrid[i]->getName() << " ";
			file << static_cast<Property*>(theGrid[i])->getOwner()->getName() << " ";
			
			if(!static_cast<Property*>(theGrid[i])->isMortgaged()){
				file << static_cast<Property*>(theGrid[i])->getImpr();
			}else{
				file << "-1";
			}
			file << endl;
		}
	}
	cout << "Your progress during this game has been saved to " <<fname<<"."<< endl;
}

void Game::setTestingMode(bool mode){
	testMode=mode;
	if (mode){
		cout<<endl;
		cout<<"Testing mode has been turned on."<<endl;
	}
}
