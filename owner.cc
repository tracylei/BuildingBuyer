#include "owner.h"

Owner::Owner(int cash): cash(cash){}

void Owner::addCash(int x){
	cash+=x;
}

