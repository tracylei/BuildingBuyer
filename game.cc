#include "controller.h"
#include "player.h"

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
	testMode = true;
	controller = NULL;
	rollUpCount = 0;
	bank = new Bank;
	die1 = new Dice;
	die2 = new Dice;
}

// Game::~Game(){
// 	for (int i = 0; i < GRID_SIZE; i++){
// 		delete Cell[i];
// 	}
// 	for (int i = 0; i<numPlayers; i++){
// 		delete players[i];
// 	}
// 	delete dice;
//	delete bank;
// }


Bank* Game::getBank(){
	return bank;
}
Player* Game::getCurrentPlayer(){
	return players[currPlayer];
}

// void Game::play(){
// 	players[currPlayer]->play();
// }


void Game::reclaimTimCups(int n){
		rollUpCount -=n;
}

Player* Game::getPlayer(string s){

	for(vector<Player*>::iterator it=players.begin(); it != players.end(); ++it){
		if ((**it).getName() == s) {
			cout << "found player" << endl;
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

// void Game::play(){
// 	players[currPlayer]->play();
// }

bool Game::getTestMode(){
	return testMode;
} 

void Game::refreshBoard(){
	controller->refreshBoard();
}

void Game::endTurn(){
//#if DEBUG
	cout<<"Turn Ended Successfully"<<endl;
//#endif


	currPlayer++;
	cout<<"number of players: "<<numPlayers<<endl;
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



 
// static void Game::incrRollUpCount(){
// 	rollUpCount++;
// }

// static int Game::getRollUpCount(){
// 	return rollUpCount;
// }

void Game::addPlayer(Player* p){
	numPlayers++;
	players.push_back(p);
	//notify controller new player is added
#if DEBUG
	cout << "adding player" << endl;
#endif
	controller->notify(p, 0 ,0);
}

// void Game::removePlayer (Player* p){
// 	numPlayers--;
// 	for (vector<int>::iterator i = players.begin(); i!= players.end(); i++){
// 		if (vec[i]->getName() == p->getName())
// 			vec.erase(i);
// 	}
// }

bool Game::isWon(){
	return (numPlayers == 1);
}

//A Player calls this to notify the controller of its move
void Game::notify(Player* p, int prevPos, int curPos){
	controller->notify(p, prevPos, curPos);

	//notfiy theGrid[curPos] that a player has arrived
}

void Game::notifyCell(int curPos){
	Property *prop = static_cast<Property*>(theGrid[curPos]);
	cout << prop->getOwner()->getName() << endl;
	
	if(prop->getOwner()->getName() == "bank" ){ //seg fault for non-property
		prop->buy(players[currPlayer]);
	}
}

void Game::init(Controller* controller){
	cout << "Game initializing.." << endl;
	
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
		//INCOMPLETE NON-PROPERTY
		if (s == "0"){
			theGrid[i] = new NonProperty(cellName);

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
				int tuition [5];
				
				for (int j = 0; j <= MAX_IMPROVEMENTS; j++){
					string tut;
					int tuitionCost;
					file>>tuitionCost;
					tuition[j] = tuitionCost;
				}

				theGrid[i] = new AcademicBuilding(cellName, purchaseCost, block, improvCost, tuition);

			}else if (s=="2"){ // Residence
				int rentFees [4];
				for (int j = 0; j < 4; j++){
						file>>rentFees[j];
					}
				theGrid[i] = new Residence (cellName, rentFees);
			}else{ //Gym
				theGrid[i] = new Gym (cellName);
			}
			static_cast<Property*>(theGrid[i])->setOwner(bank);
		}
		theGrid[i]->setIndex(i);
		theGrid[i]->setGame(this);
		i++;
	}	
}