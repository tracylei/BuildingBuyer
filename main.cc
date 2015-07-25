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
<<<<<<< HEAD
		c.init();
	}else if(argv[1] == "-load"){
		// c.loadGame(argv[2]);
	}else if(argv[1] == "-testing"){
=======
		c.play();
	}else if(string(argv[1]) == "-load"){
		c.loadGame(argv[2]);
	}else if(string(argv[1]) == "-testing"){
>>>>>>> 4356b80691a7f0e3439b247fdc2236c788c41869
		//do something
	}
	
		
}
