#ifndef __OWNER_H__
#define __OWNER_H__
#include <string>

class Player;

class Owner{
protected:
	int cash;
public:
	Owner(int);
	virtual ~Owner(){};
	void addCash(int x);
	//TESTING
	virtual std::string getName()=0;
	virtual void claimAssets(Player*)=0;
};
#endif