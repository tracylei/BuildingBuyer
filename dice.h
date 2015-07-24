#ifndef __DICE_H__
#define __DICE_H__ 

#include <iostream>
#include <cstdlib>

class Dice{
public:
	int roll();
	int SLCAction();
	int NHAction(); //generates a random NH event, returns the action

};

#endif