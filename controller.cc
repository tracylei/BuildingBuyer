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
	
}

Controller::~Controller(){
	delete game;
	delete board;
}

BoardDisplay* Controller::getBoard(){
	return board;
}

//notify board to add new player
void Controller::notify(Player *p, int prevPos, int curPos){
#if DEBUG
	cout << "controller notify" << endl;
	cout << p->getSymbol() <<prevPos <<curPos << endl;
#endif
	board->notify(p, prevPos, curPos); //why does this give segfault
}


//Called by notify board to print
void Controller::refreshBoard(){
	board->print();
}

void Controller::loadGame(const string fname){
	string pName, property, owner;
	int numPlayers, timCups, cash, position, improvements;
	char symbol;
	
	board = new BoardDisplay();
	game->init(this);
	
	//open and read game data
	ifstream data(fname.c_str());

	//initialize players
	data >> numPlayers;

	for (int i = 0; i < numPlayers; ++i){
		data >> pName >> symbol >> timCups >> cash >> position;
		Player *p = new Player(game, pName, symbol, position, cash, timCups);
		game->addPlayer(p);
		notify(p,0,position);
	}

	// add property to player
	while (data >> property){
		data >> owner >> improvements;
		// cout << property << " " <<owner << " " << improvements << endl;

		//find property and set player as owner
		Player *pl = game->getPlayer(owner);
		// cout << "player gotten" << pl->getSymbol() << pl->getCash()<< endl;
		Property *p = game->getProperty(property);
		pl->addProperty(p);
		// cout << "n: " << p->getName() << " "<< p->getID() << endl;
		board->notify(p->getID(), improvements); // notify board of any improvements
	
	}

	board->print();
	game->play();
}


void Controller::play(){
	int numPlayers;
	board = new BoardDisplay();
	//need map of players name to symbol
	
	//read in game details

	cout << "How many players are playing? (players 2-8) ";
	cin >> numPlayers;

	game->init(this);

	int i = 1;
	while(i <= numPlayers){

		char symbol;
		string name;

		//create player
		cout<< "Player "<< i << ", what is your first name?"<<endl;
		cin>>name;
		
		while (true){
			cout << name<<", please select your game piece." << endl;
			for (map<char,string>::iterator it = symbols.begin(); it != symbols.end(); it++){
				cout << it->first << " ";
			}
			cout<<endl;
			cin>>symbol;
		//check if symbol availablespot
			if (symbols.count(symbol) > 0){
				game->addPlayer(new Player(game, name, symbol, 0, 1500, 0));
				symbols.erase(symbol);
				i++;
				break;
			}else{
				cout << "That symbol is unavailable. Try Again." << endl;
			}
		}
	} 

	board->print();

	game->play();
}
