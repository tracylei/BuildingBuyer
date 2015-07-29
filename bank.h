#ifndef __BANK_H__
#define __BANK_H__
#include "owner.h"
#include "player.h"
#include "game.h"
#include <string>


class Bank: public Owner{
	Game* game;
public:
	Bank(Game* game);
	virtual ~Bank(){};
	void addCash(int x);
	//for testing
	std::string getName();
	void claimAssets(Player*);
};

#endif