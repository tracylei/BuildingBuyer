#include "cell.h"
#include "game.h"

Cell::Cell(string name):name(name){
	game = NULL;
};

void Cell::setGame(Game* game){
	this->game = game;
}
