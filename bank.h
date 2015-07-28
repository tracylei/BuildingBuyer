#ifndef __BANK_H__
#define __BANK_H__
#include "owner.h"
#include <string>


class Bank: public Owner{
public:
	Bank();
	virtual ~Bank(){};
	void addCash(int x);
	//for testing
	std::string getName();
	void claimAssets(Player*);
};

#endif