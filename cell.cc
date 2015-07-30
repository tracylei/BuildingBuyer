#include "cell.h"
#include "game.h"

using namespace std;

Cell::Cell(string name, bool buyable, bool academic):name(name), buyable(buyable), academic(academic){
	game = NULL;
};

void Cell::setGame(Game* game){
	this->game = game;
}

void Cell::setIndex(int i){
	index = i;
}

string Cell::getName(){
	return name;
}

int Cell::getID(){
	return index;
}

bool Cell::isBuyable(){
	return buyable;
}

bool Cell::isAcademic(){
	return academic;
}

