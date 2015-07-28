#ifndef _NON_PROPERTY_H_
#define _NON_PROPERTY_H_

#include "cell.h"
#include <string>

class NonProperty : public Cell{
	//name field from super class
public:
	NonProperty(std::string name);
	virtual ~NonProperty(){};
	void doAction(Player* p);
	void slcAction (Player* p);
	void needlesAction (Player* p);

};

#endif