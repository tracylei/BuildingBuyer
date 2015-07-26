#ifndef _RESIDENCE_H_
#define _RESIDENCE_H_

#include "property.h"
extern const int RESIDENCE_COST;

class Residence : public Property{
	int* rent;
public:
	Residence(std::string bldgName, int* rent);
	int getRent();
};

#endif
