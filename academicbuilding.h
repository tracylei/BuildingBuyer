#ifndef _ACADEMICBUILDING_H_
#define _ACADEMICBUILDING_H_

#include "property.h"
#include <string>


class AcademicBuilding : public Property{
	//From super class Property - string bldgName; int cost; Player* ownerk;
	int rent, imprCost;
	int *tuition;
	//voivvd loadBuildingInfo(istream f);
public:
	AcademicBuilding(std::string Name, int cost, std::string block, int improvCost, int *tuition);
	//Build n improvements
	void improve(int n);
	// void chargeFee(Player* p);
};

#endif