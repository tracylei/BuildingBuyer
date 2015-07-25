#include "game.h"
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
	testMode = false;
	controller = NULL;
	rollUpCount = 0;
	bank = new Bank;
	dice = new Dice;
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

void Game::play(){
	players[currPlayer]->play();
}

bool Game::getTestMode(){
	return testMode;
} 

void Game::endTurn(){
#if DEBUG
	cout<<"Turn Ended Successfully"<<endl;
#endif
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
		play();
	}
}

void Game::refreshBoard(){
	controller->refreshBoard();
}

int Game::rollDice(){
	return dice->roll();
}

// static void Game::reclaimTimsCups(int n){
// 	rollUpCount -=n;
// }
 
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

					// cout << tuitionCost << " ";
					tuition[j] = tuitionCost;
				}
				theGrid[i] = new AcademicBuilding(cellName, purchaseCost, block, improvCost, tuition);

			}else if (s=="2"){ // Residence
				int rentFees [4];
				for (int j = 0; j < 4; j++){
						file>>rentFees[j];
					}
				theGrid[i] = new Residence (cellName, purchaseCost, rentFees);
			}else{ //Gym
				theGrid[i] = new Gym (cellName, purchaseCost);
			}
			static_cast<Property*>(theGrid[i])->setOwner(bank);
		}
		i++;
	}	
}