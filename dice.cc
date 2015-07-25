#include "dice.h"


Dice::Dice(){
	srand(time(NULL));
}

int Dice::roll(){
	//return rand() % 6 + 1;

	return rand() % 6 + 1;
}

int SLCAction(){

}

int NHAction(){
	// int roll = rand(2041) % 100;

	// if (roll < 1/9){
	// 	return (rand() % 1 == 1) ? 200 : -200;
	// }else if(roll < 2/9){
	// 	return (rand() % 1 == 1) ? 100 : -100; 
	// }else if(roll < 1/3){
	// 	return (rand() % 1 == 1) ? 50 : -50; 
	// }else{
	// 	return 25;
	// }
}