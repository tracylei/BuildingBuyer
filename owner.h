#ifndef __OWNER_H__
#define __OWNER_H__
#include <string>

class Owner{
	int cash;
public:
	Owner(int);
	void addCash(int x);
	//TESTING
	virtual std::string getName()=0;
};
#endif