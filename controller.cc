#include "controller.h"
#include "academicbuilding.h"

#include <fstream>
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
	board->notify(p, prevPos, curPos); //why does this give segfault
}

void Controller::notifyImprove (int index, int numImprov){
	board->notify(index, numImprov);
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

		//play is on DC Tim's line
		if(position == 10){
			int inJail, jailTurn;
			cin >> inJail;

			if(inJail){
				cin >> jailTurn; //TODO, update turns in jail
				p->goToJail();
			}
		}
	}

	// add property to player
	while (data >> property){
		data >> owner >> improvements;
		// cout << property << " " <<owner << " " << improvements << endl;
		

		//find property and set player as owner
		Player *pl = game->getPlayer(owner);
		Property *p = game->getProperty(property);

		if(improvements == -1){ //property is mortgaged
			p->setMortgaged(true);
		}

		pl->addProperty(p);
		// cout << "n: " << p->getName() << " "<< p->getID() << endl;
		if (p->isAcademic()){
			board->notify(p->getID(), improvements); // notify board of any improvements
			static_cast<AcademicBuilding*>(p)->setImprove(improvements);
		}

	}

	board->print();
	play(false);
}


void Controller::init(){

	int numPlayers;
	board = new BoardDisplay();
	//need map of players name to symbol
	
	//read in game details

	cout << "How many players are playing? (Please enter a number between 2-8.)" << endl;
	string strPlayers;
	getline(cin,strPlayers);
	istringstream iss(strPlayers);
	iss >> numPlayers;

	while (numPlayers<2 || numPlayers>8){
		cout<<"Building Buyer is a 2 to 8 player game. Please enter a valid number of players."<<endl;
		cout << "How many players are playing? (Please enter a number between 2-8.)" << endl;
		getline(cin,strPlayers);
		istringstream iss(strPlayers);
		iss >> numPlayers;
	}


	game->init(this);

	int i = 1;
	while(i <= numPlayers){

		string symbol;
		string name;

		//create player
		cout<< "Player "<< i << ", what is your first name?"<<endl;
		getline(cin, name);
		
		while (true){
			cout << name<<", please select your game piece." << endl;
			for (map<char,string>::iterator it = symbols.begin(); it != symbols.end(); it++){
				cout << it->first << " ";
			}
			cout<<endl;
			getline(cin,symbol);
		//check if symbol availablespot
			if (symbol.length()==1&&symbols.count(symbol[0]) > 0){
				game->addPlayer(new Player(game, name, symbol[0], 0, 1500, 0));
				symbols.erase(symbol[0]);
				i++;
				break;
			}else{
				cout << "That symbol is unavailable. Please try Again." << endl;
			}
		}
	} 

	board->print();

	play(false);
}

void Controller::rollInJail(int roll1, int roll2){
		game->getCurrentPlayer()->setJailRolls(roll1, roll2);
		if (roll1 == roll2){
			cout<<"You rolled two "<<roll1<<"'s!"<<endl;
			game->getCurrentPlayer()->leaveJail();
			play(true);
		} 
		else if (game->getCurrentPlayer()->getTurnsInJail() != 3){
			cout<<endl;
			cout<<"Unfortunately, you rolled a "<<roll1<<" and a "<<roll2<<"."<<endl;
			cout<<"Please wait another turn to try again. You can still buy/sell improvements and issue similar commands."<<endl;
			play(true);
		}
		else{
			cout<<endl;
			cout<<"Unfortunately, you rolled a "<<roll1<<" and a "<<roll2<<"."<<endl;
			cout<<"Since this is your third turn in the line, that was your last chance to leave by rolling a double."<<endl;
			cout<<"Now you must either use a Roll Up the Rim Cup or pay $50. Please issue a \"cup\" command, or \"pay\" command."<<endl;
			cout <<"You currently have "<< game->getCurrentPlayer()->getTimCups()<<" Roll Up the Rim Cups and $" << game->getCurrentPlayer()->getCash()<<"."<<endl;
			string cmd;
			getline (cin, cmd);
			while (cmd!="cup" && cmd != "pay"){
				cout<<"Please only use the \"cup\", or \"pay\" commands."<<endl;
				getline(cin, cmd);
			}
			if (cmd=="cup"){
				if (game->getCurrentPlayer()->getTimCups() < 1){
					cout <<"Sorry, you don't have any Roll Up the Rim Cups to use. You must use the \"pay\" command to pay $50 and leave."<<endl;
					cmd = "";
					string cmd;
					getline (cin, cmd);
					while (cmd != "pay"){
						cout<<"Please only use the \"pay\" command."<<endl;
						getline(cin, cmd);
					}
				}
				else{
					game->reclaimTimCups(1);
					game->getCurrentPlayer()->useTimCup();
					game->getCurrentPlayer()->leaveJail();
					play(true);
					cout<<"You now have one less Roll Up the Rim Cup."<<endl;
				}
			}
			if (cmd=="pay"){
				// if (game->getCurrentPlayer()->pay(50, game->getBank()))
					game->getCurrentPlayer()->leaveJail();
				play(true);
			}
		}//Does not roll double on third turn
}//Rolling the dice


void Controller::playInJail(){
	cout << game->getCurrentPlayer()->getName() << "'s turn."<<endl;
	cout << "You are currently stuck in the DC Tim's Line."<<endl;
	cout << "The only way out is rolling doubles, using a Roll Up the Rim Cup, or paying $50 (for some gourmet coffee)."<<endl;
	cout<< "Would you like to issue a \"roll\" command to row the dice, \"cup\" command to use a Roll Up the Rim cup, of \"pay\" command to buy coffee and leave?"<<endl;

	string input;
	string cmd;
	getline (cin, input);
	istringstream iss (input);
	iss>>cmd;
	while (cmd!="roll" && cmd!="cup" && cmd != "pay"){
		cout<<"Please only use the \"roll\", \"cup\", or \"pay\" commands."<<endl;
		getline(cin, cmd);
	}

	if (cmd == "roll")
		if (game->getTestMode()){
			int r1, r2;
			iss>>r1>>r2;
			rollInJail(r1, r2);
		}
		else{
			rollInJail(game->rollDie1(), game->rollDie2());
		}
	else if (cmd == "cup"){
		if (game->getCurrentPlayer()->getTimCups() < 1){
			cout <<"Sorry, you don't have any Roll Up the Rim Cups to use. Please issue a different command."<<endl;

			string cmd;
			getline (cin, cmd);
			while (cmd!="roll" && cmd != "pay"){
				cout<<"Please only use the \"roll\", or \"pay\" commands."<<endl;
				getline(cin, cmd);
			}
			if (cmd == "roll")
				rollInJail(game->rollDie1(), game->rollDie2());
			else if (cmd == "pay"){
				// if (game->getCurrentPlayer()->pay(50, bank))
					game->getCurrentPlayer()->leaveJail();
			}
		}
		else{
			game->reclaimTimCups(1);
			game->getCurrentPlayer()->useTimCup();
			game->getCurrentPlayer()->leaveJail();
			//play(); //need to set rolled to true
			cout<<"You now have one less Roll Up the Rim Cup."<<endl;
		}
	}
	else if(cmd == "pay"){
			// if (game->getCurrentPlayer()->pay(50, bank))
			game->getCurrentPlayer()->leaveJail();
	}
}

void Controller::play(bool rolled){
	cout << game->getCurrentPlayer()->getName() << "'s turn. Please enter your commands." << endl;
	//player commands..

	string input;
	string cmd;
	while(getline(cin,input)){
		if (input.length()==0)
			continue;
#if DEBUG
		cout<<"Reading commands..."<<endl;
#endif
		cmd = "";
		istringstream iss(input);
		iss >> cmd;
		if (cmd == "roll"){
#if DEBUG
			cout<<"Read in roll..."<<endl;
#endif
			if (!rolled) {
#if DEBUG
				cout<<game->getCurrentPlayer()->getName()<<" rolls the dice"<<endl;
#endif		
				int roll1, roll2, numRolls = 0;
				rolled=true;
				if(game->getTestMode()){
					int r1, r2;
					iss >> r1 >> r2;
					roll1 = r1;
					roll2 = r2;
					numRolls = 1;
				}else{
					roll1 = game->rollDie1();
					roll2 = game->rollDie2();
					numRolls = 1;
				}
					//Dealing with rolling doubles
				while (roll1 == roll2){
						if (numRolls == 3){
							game->getCurrentPlayer()->goToJail();
							board->print();
							cout<<"Uh oh, you rolled 3 doubles in a row. You've been moved to the DC Tim's Line because you stayed up all night programming and NEED caffeine."<<endl;
							break;
						}
						else{
							game->getCurrentPlayer()->move(roll1, roll2);
							cout<<"Yay, a double!"<<endl;
							cout<<"You rolled a "<<roll1<<" and a "<<roll2<<". Please roll again."<<endl;

							string input;
							string cmd;
							getline(cin,input);

							cout<<"input is:"<<input<<endl;
							istringstream iss(input);
							iss >> cmd;
							while (cmd!="roll"){
								cout<<"You need to roll again before using another command. Please issue the roll command again."<<endl;
								getline(cin,input);
								istringstream iss(input);
								iss>>cmd;
							}
							if(game->getTestMode()){
								int r1, r2;
								iss >> r1 >> r2;
								roll1 = r1;
								roll2 = r2;
								cout <<"r1 is: "<<r1<<endl;
								cout <<"r2 is: "<<r2<<endl;
							}else{
								roll1 = game->rollDie1();
								roll2 = game->rollDie2();
							}
							numRolls++;
						}
					}

					//Process dice rolls into movs
					if (!game->getCurrentPlayer()->isInJail()){
						game->getCurrentPlayer()->move (roll1, roll2);
					}
				
			}
			else {
					cout<<"You cannot roll again on this turn. Please choose another command."<<endl;
			}
		//What if asks to roll twice
		}else if (cmd == "next"){//end turn
			if (!rolled)
				cout<<"You can still roll on this turn. Please roll the dice or choose another command."<<endl;
			else
				game->endTurn();

		}else if (cmd == "trade"){
			string player, give, want;
			Player *p;

			iss >> player >> give >> want;

			//find player.
			p = game->getPlayer(player); 
			game->getCurrentPlayer()->trade(p, give, want);
		}else if (cmd == "improve"){
			string propName, action;
			iss >> propName >> action;


			//Check that the current player actually owns the property
			int numProp = game->getCurrentPlayer()->getProperties().size();
			bool owned = false;
			string block;
			//index of the property
			int index;
			for (unsigned int i = 0; i < numProp; i++){
				if (game->getCurrentPlayer()->getProperties()[i]->getName() == propName){
					owned=true;
					index = game->getCurrentPlayer()->getProperties()[i]->getID();
					block=game->getCurrentPlayer()->getProperties()[i]->getBlock();
				}
			}

			if (!owned){
				cout<<"Sorry, you can only buy/sell improvements on properties that you own."<<endl;
			}
			else if(static_cast<AcademicBuilding*>(game->getTheGrid(index))->isMortgaged()){
				cout<<"Sorry, improvements can only be built on unmortgaged properties."<<endl;
			}
			else{
					if (action == "buy"){
						bool monopoly = game->getCurrentPlayer()->hasMonopoly(block);
						if (!monopoly){
							cout<<"Sorry, you can only purchase improvements on a property when you own all properties in its block."<<endl;
						}else if (monopoly){
								static_cast<AcademicBuilding*>(game->getTheGrid(index))->improve(1);
								cout<<"You've successfully purchased an improvement for "<<propName<<" for $";
								cout<<static_cast<AcademicBuilding*>(game->getTheGrid(index))->getImprCost()<<"."<<endl;
						}
						else if (static_cast<AcademicBuilding*>(game->getTheGrid(index))->getImpr()>5){
								cout<<"Sorry, you can only have a maximum of 5 improvements on each improvable property."<<endl;
						}
					}
					else if (action == "sell"){
							
							if (static_cast<AcademicBuilding*>(game->getTheGrid(index))->getImpr()<=0){
								cout<<"Sorry, there are no improvements on "<<propName<<" for you to sell."<<endl;
							}
							else{
								static_cast<AcademicBuilding*>(game->getTheGrid(index))->sellImprove(1);
								cout<<"You've successfully sold an improvement for "<<propName<<" for $";
								cout<<static_cast<AcademicBuilding*>(game->getTheGrid(index))->getImprCost()/2<<"."<<endl;
							}
							continue;
					}
			}


		}else if (cmd == "mortgage"){
			string propName;
			iss >> propName;

			for(unsigned int n = 0; n < game->getCurrentPlayer()->getProperties().size(); n++){
			Property *temp = game->getCurrentPlayer()->getProperties().at(n);
				if (temp->getName() == propName){ 
						game->getCurrentPlayer()->mortgage(temp);	 
						break;
				}
			}
		}else if (cmd == "unmortgage"){
			string propName;
			iss >> propName; 
			for(unsigned int n = 0; n < game->getCurrentPlayer()->getProperties().size(); n++){ 

				Property *temp = game->getCurrentPlayer()->getProperties().at(n);
				if (temp->getName() == propName){
					game->getCurrentPlayer()->unmortgage(temp);
					break;
				}
			}
		}else if (cmd == "bankrupt"){
			cout<<"You can only declare bankruptcy when you owe someone more than you can pay."<<endl;
		}else if (cmd == "assets"){
			game->getCurrentPlayer()->displayAssets();
		}else if(cmd == "save"){
			string fileName;
			iss >> fileName;
			ofstream ofs (fileName, ofstream::out);
			int numPlayers = game->getNumPlayers();
			ofs<<numPlayers<<endl;
			for (int i = 0; i<numPlayers; i++){
				ofs<<game->getPlayer(i)->getName()<<" "<<game->getPlayer(i)->getSymbol()<<" ";
				ofs<<game->getPlayer(i)->getTimCups()<<" "<<game->getPlayer(i)->getCash()<<" ";
				ofs<<game->getPlayer(i)->getCurPos();
				if (game->getPlayer(i)->isInJail()){
					ofs<<" 1 "<<game->getPlayer(i)->getTurnsInJail();
				}
				else if (game->getPlayer(i)->getCurPos() == 10){
					ofs<<" 0";
				}
				ofs<<endl;
			}
			for (int i = 0; i < 40; i++){
				if (game->getTheGrid(i)->isBuyable()){
					ofs<<game->getTheGrid(i)->getName()<<" ";
					string ownerName = static_cast<Property*>(game->getTheGrid(i))->getOwnerName();

					if (ownerName=="bank")
						ofs<<"BANK ";
					else 
						ofs<<ownerName<<" ";

					if (!static_cast<Property*>(game->getTheGrid(i))->isMortgaged())
						ofs<<static_cast<Property*>(game->getTheGrid(i))->getImpr()<<endl;
					else
						ofs<<"-1"<<endl;

				}
			}
			ofs.close();
			cout<<"Your progress in this game has been saved to "<<fileName<<".";

		}else{
			cout<<"Your command could not be recognized. Please enter another command."<<endl;
		}
	}
//}

}
