#ifndef _GYM_H_
#define _GYM_H_

#include "property.h"
#include <string>
extern const int GYM_COST;

class Gym : public Property{
public:
	Gym(std::string);
	virtual ~Gym(){};
	void doAction(Player* p);
	int getValue();
};

#endif
