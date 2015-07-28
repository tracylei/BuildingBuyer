#include "nonproperty.h"
#include "player.h"
#include <iostream>
#include <string>
#include "game.h"
#include <unistd.h>


using namespace std;



NonProperty::NonProperty(std::string name): Cell(name, false, false){
}

void NonProperty::doAction(Player* p){
	if (name == "OSAP"){
		cout<<"Congrats on collecting OSAP! Here is $200."<<endl;
		cout<<"You had $"<<p->getCash()<<" before."<<endl;
		p->addCash(200);
		cout<<"Now you have $"<<p->getCash()<<"."<<endl;

	}
	else if (name == "GOTOTIMS"){
		p->goToJail();
		cout<<"You've just been moved to the DC TIM'S LINE for landing on GO TO TIMS."<<endl;
		cout<<"Hopefully you get your coffee before class starts."<<endl;
	}else if(name == "GooseNesting" ){
		cout<<"YOU JUST GOT ATTACKED BY A FLOCK OF GEESE! RUN!!!!"<<endl;
	}else if(name == "TUITION"){
		cout<<"It's that time of year again. Would you like to pay $300 in tuition (using the \"tuition\" command),";
		cout<<" or pay 10% of your net worth (using the \"worth\" command)?"<<endl; 
		int worth = p->getNetWorth();
		cout<<"Your net worth is $"<<worth<<"."<<endl;

		string input;
		getline (cin, input);
		while (input!="tuition" && input!="worth"){
			cout<<"Please only use the \"tuition\" and \"worth\" command."<<endl;
			getline (cin, input);
		}
		if (input == "tuition"){
			cout<<"Since you chose to pay $300 in tuition, $300 will be deducted from your bank account."<<endl;
			cout<<"You currently have $"<<p->getCash()<<"."<<endl;
			if (p->pay(300, game->getBank()))
				cout<<"After paying, you have $"<<p->getCash()<<"."<<endl;
		}
		else{
			cout<<"Since you chose to pay 10% of your net worth, $"<<worth*.1<<" will be deducted from your bank account."<<endl;
			cout<<"You currently have $"<<p->getCash()<<"."<<endl;
			if (p->pay(worth*.1, game->getBank()))
				cout<<"After paying, you have $"<<p->getCash()<<"."<<endl;
		}
	}
	else if(name == "COOP FEE"){
		cout<<"You've landed on CO-OP FEE. Immediately pay $150 to the School."<<endl;
		cout<<"You had $"<<p->getCash()<<"before paying."<<endl;
		if (p->pay(150, game->getBank()))
			cout<<"Now you have $"<<p->getCash()<<"."<<endl;
	}
	else if(name == "SLC"){
		bool giveTimCup = false;
		if (game->getTimCupCount()<4){
			giveTimCup = game->die1->giveTimCup();
		}
		if (giveTimCup){
			cout<<"Congratulations! You found a Roll Up the Rim Cup in SLC!"<<endl;
			cout<<"You originally had "<<p->getTimCups()<<" Roll Up the Rim Cups."<<endl;
			p->incrTimCups();
			cout<<"You now have "<<p->getTimCups()<<" Roll Up the Rim Cups."<<endl;
		}else{
			slcAction(p);
		}
	}
	else if(name == "NEEDLESHALL"){
		bool giveTimCup = false;
		if (game->getTimCupCount()<4){
			giveTimCup = game->die1->giveTimCup();
		}
		if (giveTimCup){
			cout<<"Congratulations! You found a Roll Up the Rim Cup in Needl's Hall!"<<endl;
			cout<<"You originally had "<<p->getTimCups()<<" Roll Up the Rim Cups."<<endl;
			p->incrTimCups();
			cout<<"You now have "<<p->getTimCups()<<" Roll Up the Rim Cups."<<endl;
		}else{
			needlesAction(p);
		}

	}
	
}


void NonProperty::needlesAction(Player* p){
	int money = game->die1->NHAction();
	if (money<0){
		cout<<"You are going to get charged $"<<-money<<" for landing on Needle's Hall."<<endl;
		p->pay(-money,game->getBank());
	}
	else{
		cout<<"Congrats! You found $"<<money<<" while walking around Needle's Hall."<<endl;
		p->addCash(money);
	}
}


void NonProperty::slcAction(Player* p){
	int action = game->die1->SLCAction();
	if (action == 23){
		p->goToJail();
		cout<<"The Tim's line at SLC was too long for your liking so you (have been) moved to the DC Tim's Line."<<endl;
	}
	else if(action == 24){
		cout<<"You got a text saying your OSAP loan was deposited to your account! Quick! Go collect it!"<<endl;
		p->move(-2,0);
	}
	else {

		cout<<"You will be teleported ";
		if (action == -1)
			cout<<"back 1 cell";
		else if (action == 1)
			cout<<"forward 1 cell";
		else if (action > 1)
			cout<<"forward "<<action<<" cells";
		else
			cout<<"back "<<-action<<" cells";

		cout<<" from SLC in 3 seconds."<<endl;
		usleep(1000000);
		cout<<"3..."<<endl;
		usleep(1000000);
		cout<<"2.."<<endl;
		usleep(1000000);
		cout<<"1."<<endl;
		usleep(1000000);
		p->slcMove(action);
	}

}




