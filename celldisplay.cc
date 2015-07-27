#include "celldisplay.h"

using namespace std; 

CellDisplay::CellDisplay():numImprov(0){
	for (int i = 0; i < 8; i++){
		players[i] = ' ';
	}
}
CellDisplay::CellDisplay(string name, int id, int isProperty=1, int numImprov=0):name(name), id(id), isProperty(isProperty),numImprov(numImprov){
	for (int i = 0; i < 8; i++){
		players[i] = ' ';
	}
}

string CellDisplay::getName(){
	return name;
}

bool CellDisplay::getIsProperty(){
	return isProperty;
}

char *CellDisplay::getPlayers(){
	return players;
}

int CellDisplay::getImpr(){
	return numImprov;
}

void CellDisplay::addImpr(){
	numImprov++;
}
void CellDisplay::sellImpr(){
	numImprov--;
}

void CellDisplay::setPlayer(char p){
	for(int i = 0; i < 8; ++i){
		if (players[i] == ' ') {players[i] = p; return;}
	}
}

void CellDisplay::removePlayer(char p){
	for(int i = 0; i < 8; ++i){
		if (players[i] == p) {players[i] = ' '; return;}
	}
}

