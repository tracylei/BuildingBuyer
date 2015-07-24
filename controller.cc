#include "controller.h"

using namespace std;

Controller::Controller(){
	game = new Game();
	board = NULL;

	symbols['G'] = "Goose";
	symbols['B'] = "GRT BUS";
	symbols['D'] = "Tim Hortons Doughnut";
	symbols['P'] = "Professor";
	symbols['S'] = "Student";
	symbols['$'] = "Money";
	symbols['L'] = "Laptop";
	symbols['T'] = "Pink tie";
	// for (map<char,string>::iterator it = symbols.begin(); it != symbols.end(); it++){
	// 		cout << it->first << " ";
	// }
}

Controller::~Controller(){
	delete game;
	delete board;
}

BoardDisplay* Controller::getBoard(){
	return board;
}
// void Controller::loadGame(const string fname){
// 	//open and read game data
// 	ifstream data(fname.c_str());

// 	string pName, property, owner;
// 	int numPlayers, timCups, money, position, improvements;
// 	char symbol;

// 	//initialize players
// 	data >> numPlayers;
// 	for (int i = 0; i < numPlayers; ++i){
// 		data >> pName >> symbol >> timCups >> money >> position;
		
// 		Player *p = new Player(pName, symbol, money, position, timCups);
// 		game->players.push_back(p);
		
// 		board->notify(p,position,position);
// 	}

// 	//initialize game cells
// 	while (data >> property){
// 		data >> symbol >> owner >> improvements;
// 		//TODO
// 		//add property to player
// 	}
// }

//notify board to add new player
void Controller::notify(Player *p, int prevPos, int curPos){
	cout << "controller notify" << endl;
	cout << p->getSymbol() <<prevPos <<curPos << endl;
	
	// board->notify(p, prevPos, curPos); //why does this give segfault
}

void Controller::play(){
	int numPlayers;
	board = new BoardDisplay();
	//need map of players name to symbol
	
	//read in game details

	cout << "How many players are playing? (players 2-8)";
	cin >> numPlayers;
	
	int i = 1;
	while(i <= numPlayers){

		char symbol;
		string name;

		//create player
		cout << "Player " << i << " please select your game piece." << endl;
		for (map<char,string>::iterator it = symbols.begin(); it != symbols.end(); it++){
			cout << it->first << " ";
		}
		cout << endl;
		cin >> symbol;

		//check if symbol availablespot
		if (symbols.count(symbol) > 0){
			game->addPlayer(new Player(name, symbol, 0, 1500, 0));
			symbols.erase(symbol);
			i++;
		}else{
			cout << "That symbol is unavailable. Try Again." << endl;
		}
	} 

	game->init(this);

	board->print();
}
