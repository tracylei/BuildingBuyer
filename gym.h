#ifndef _GYM_H_
#define _GYM_H_

#include "property.h"
#include <string>
extern const int GYM_COST;

class Gym : public Property{
public:
	Gym(std::string);
	// void doAction(Player* p);
};

#endif
