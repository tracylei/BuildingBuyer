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
		c.play();
	}else if(string(argv[1]) == "-load"){
		c.loadGame(argv[2]);
	}else if(string(argv[1]) == "-testing"){
		//do something
	}
	
		
}
