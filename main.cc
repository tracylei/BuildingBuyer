#include "controller.h"
#include <iostream>

using namespace std;

int main(int argc, char const *argv[]){
	cout << "-----------------------------------------" << endl;
	cout << "| ###   ###   #####   ###   ###   ###   |" << endl;
	cout << "| #  #  #  #     #   #   # #   # #   #  |" << endl;
	cout << "| ####  ####    #    #   # #   # #   #  |" << endl;
	cout << "| #   # #   #  #     #   # #   # #   #  |" << endl;
	cout << "| ####  ####  #       ###   ###   ###   |" << endl;
	cout << "-----------------------------------------" << endl;
	cout << endl;
	cout << "Welcome to BuildingBuyer 7000!!" <<endl;
	
	Controller c;

	if(argc == 1){
		c.init();
	}else if(argc == 2){
		if(string(argv[1]) == "-testing"){
			c.init(true);
		}else if(string(argv[1]) == "-airport"){
			c.init(false,"airport.txt");
		}
	}else if(argc == 3){
		if(string(argv[1]) == "-load"){
			c.loadGame(argv[2]);
		}
	}else if(argc == 4){
		if(string(argv[1]) == "-load" && string(argv[3]) == "-testing"){
			c.loadGame(argv[2],true);
		}else if(string(argv[2]) == "-load" && string(argv[1]) == "-testing"){
			c.loadGame(argv[3],true);
		}
	}
	
		
}
