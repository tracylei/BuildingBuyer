#ifndef __DICE_H__
#define __DICE_H__ 

#include <iostream>
#include <cstdlib>

class Dice{
public:
	Dice();
	int roll();
	int SLCAction(); //generates a random SLC event, returns the action
	int NHAction(); //generates a random NH event, returns the action
	bool giveTimCup();
};

#endif