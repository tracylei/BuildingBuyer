#include "dice.h"

int Dice::roll(){
	return srand(2041) % 6 + 1;
}

int SLCAction(){

}

int NHAction(){
	int roll = srand(2041) % 100;

	if (roll < 1/9){
		return (srand() % 1 == 1) ? 200 : -200;
	}else if(roll < 2/9){
		return (srand() % 1 == 1) ? 100 : -100; 
	}else if(roll < 1/3){
		return (srand() % 1 == 1) ? 50 : -50; 
	}else{
		return 25;
	}
}