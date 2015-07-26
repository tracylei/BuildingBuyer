#ifndef _NON_PROPERTY_H_
#define _NON_PROPERTY_H_

#include "cell.h"
#include <string>

class NonProperty : public Cell{
	//name field from super class
public:
	NonProperty(std::string name);
	// virtual doAction() = 0;
};

#endif