#ifndef _ACADEMICBUILDING_H_
#define _ACADEMICBUILDING_H_

#include "property.h"
#include <string>


class AcademicBuilding : public Property{
	//From super class Property - string bldgName; int cost; Player* ownerk;
	int imprCost;
	int *tuition;
	//voivvd loadBuildingInfo(istream f);
public:
	AcademicBuilding(std::string Name, int cost, std::string block, int improvCost);
	virtual ~AcademicBuilding();
	void setTuition (int index, int tutCost);
	//Build n improvements
	void improve(int n);
	void sellImprove(int);
	void setImprove(int);
	void doAction(Player* p);
	int getValue();
	int getImprCost();
};

#endif
