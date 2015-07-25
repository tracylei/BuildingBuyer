#include "cell.h"
#include "game.h"

Cell::Cell(string name):name(name){
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

