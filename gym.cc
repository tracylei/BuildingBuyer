#include "gym.h"


Gym::Gym(std::string bldgName): Property(bldgName, 150, false){
}

void Gym::doAction(Player* p){
	if (owner->getName()!= "BANK" && static_cast<Player*>(owner)->getSymbol()!=p->getSymbol()){
		if (mortgaged){\
			cout<<"You were not charged for landing on "<<name<<" because it is currently mortgaged."<<endl;
		}else {
			cout<<"You've landed on a gym owned by "<<owner->getName()<<". Please roll the dice using the roll command to determine ";
			cout<<"the fee you have to pay."<<endl;
			string cmd;
			string input;
			getline(cin, input);
			istringstream iss(input);
			iss>>cmd;
			while (cmd != "roll"){
				istringstream iss2(input);
				iss2>>cmd;
				cout<<"Please issue the roll command to determine the fee you need to pay."<<endl;
				getline(cin, input);
			}
			int roll1, roll2;
			if (game->getTestMode()){
				iss>>roll1>>roll2;
			}
			else{
				roll1=game->rollDie1();
				roll2=game->rollDie2();
			}
			cout<<"You've rolled a "<<roll1<<" and a "<<roll2<<" so you will have to pay "<<2*(roll1+roll2)<<"."<<endl;
			p->pay(2*(roll1+roll2), owner);
		}
	}
}


int Gym::getValue(){
	return cost;
}

