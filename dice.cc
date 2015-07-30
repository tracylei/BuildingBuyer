#include "dice.h"


Dice::Dice(){
	srand(time(NULL));
}

int Dice::roll(){

	return (rand() % 6 + 1);
}

int Dice::SLCAction(){
	int roll = rand() % 24 + 1;

	if(roll <=3){
		return -3;
	}
	else if (roll<=7){
		return -2;
	}
	else if (roll<=11){
		return -1;
	}
	else if (roll<=14){
		return 1;
	}
	else if (roll<=18){
		return 2;
	}
	else if (roll<=22){
		return 3;
	}
	else if(roll == 23){
		return 23;
	}
	else{
		return 24;
	}

}

int Dice::NHAction(){
	int roll = rand() % 18 + 1;

	if (roll <= 1){
		return -200;
	}else if(roll <= 3){
		return -100; 
	}else if(roll <= 6){
		return -50;
	}else if (roll <= 12){
		return 25;
	}else if (roll <= 15){
		return 50;
	}
	else if(roll <=17){
		return 100;
	}
	else{
		return 200;
	}

}


bool Dice::giveTimCup(){
	int roll = rand () % 100 + 1;
	if (roll == 1)
		return true;
	return false;
}


