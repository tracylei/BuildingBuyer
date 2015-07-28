#include "boarddisplay.h"

using namespace std;

BoardDisplay::BoardDisplay(){
	ifstream data("celldisplay.txt");
	string name;
	int i = 0;
	int isProperty, numImpr;
	while(data >> name){
		// cout << i<< name << isProperty <<endl;
		data >> isProperty >> numImpr;
		cells[i] = CellDisplay(name, i, isProperty, numImpr);
		++i;
	}

}

void BoardDisplay::notify(Player *p, int oldPos, int newPos){//need old and new cells
#if TESTING
	cout<<"set"<<endl;
	cout << "set player.." << oldPos << newPos<< endl;
#endif
	//remove player from previous cell
	if(oldPos != newPos){
		 cells[oldPos].removePlayer(p->getSymbol());
	}
	cells[newPos].setPlayer(p->getSymbol()); 
	//update number of players on the cell
}

void BoardDisplay::notify(int id, int n){ //need property id
	if (n>0){
		for (;n > 0; --n){
			cells[id].addImpr(); 
		}
	}
	else{
		for (;n < 0; n++){
			cells[id].sellImpr();
		}
	}
}


string BoardDisplay::printPlayers(int cell){
	ostringstream os;
	for (int i = 0; i < 8; ++i){
		char *players = cells[cell].getPlayers();
		os << players[i];
	}
	return os.str();
}

string BoardDisplay::printImpr(int n){
	ostringstream os;
	if (n >=5) {os << "WAP";}
	else{
		for (int i = 0; i < n; ++i){
			os << 'I';
		}
	}
	return os.str();
}		

void BoardDisplay::print(){
	cout << "----------------------------------------------------------------------------------------------------" << endl;
	//line 2
	for (int i = 20; i <= 30; ++i){
		if (cells[i].getName() == "Goose_Nesting"){
			cout << "|" <<setw(8)<<left<< "Goose" << "" ;
		}else if (cells[i].getName() == "NEEDLES_HALL"){
			cout <<"|" << setw(8) << left <<"NEEDLES";
		}else if(cells[i].getName() == "GO_TO_TIMS"){
			cout <<"|" << setw(8) << left <<"GO TO" << "|";
		}else if(cells[i].getName() == "V1" || cells[i].getName() == "CIF"){
			cout <<"|" << setw(8) << cells[i].getName();
		}else{
			cout << "|" << setw(8) << printImpr(cells[i].getImpr()); //if building has improvemnts add it here...
		}
	}
	cout << endl;

	//line 3
	for (int i = 20; i <= 30; ++i){
		if (cells[i].getName() == "Goose_Nesting"){
			cout << "|" <<setw(8)<< left << "Nesting" << "" ;
		}else if (cells[i].getName() == "NEEDLES_HALL"){
			cout <<"|" << setw(8) << left << "HALL";
		}else if(cells[i].getName() == "GO_TO_TIMS"){
			cout <<"|" << setw(8) << left << "TIMS"<< "|";
		}else if(cells[i].getName() == "V1" || cells[i].getName() == "CIF"){
			cout <<"|        ";
		}else{
			cout << "|--------";
		}
	}
	cout << endl;

	//line 4
	for (int i = 20; i <= 30; ++i){
		if (!cells[i].getIsProperty()){
			cout << "|" <<setw(8) << " " ;
			if(cells[i].getName() == "GO_TO_TIMS") cout << "|";
		}else{
			cout << "|" << setw(8) << left << cells[i].getName();
		}
	}
	cout << endl;
	//line 5
	
	for (int i = 20; i <= 30; ++i){
		cout <<"|" << printPlayers(i); //set players here
	}
	cout << "|" <<endl;

	for (int i = 20; i <= 30; ++i){
		cout <<"|" << "        "; 
	}
	cout << "|" <<endl;
	
	//line 7
	cout << "|--------------------------------------------------------------------------------------------------|" << endl;


	//8 properties on vertical edges
	cout << "|" << setw(8) << printImpr(cells[19].getImpr()) << "|" << setw(80) << " " << "|" << setw(8) << printImpr(cells[31].getImpr()) << "|" << endl;
	cout << "|--------|" << setw(80) << " " << "|--------|" << endl;
	cout << "|" << setw(8) << left << cells[19].getName() << "|" << setw(80) << " " << "|" << setw(8) << left << cells[31].getName() << "|" << endl;	
	cout << "|" << printPlayers(19) << "|" << setw(80) << " " << "|" << printPlayers(31) <<"|" << endl;
	cout << "|        |" << setw(80) << " " << "|        |" << endl;
	cout << "|--------|" << setw(80) << " " << "|--------|" << endl;

	cout << "|" << setw(8) << printImpr(cells[18].getImpr()) << "|" << setw(80) << " " << "|" << setw(8) << printImpr(cells[32].getImpr()) << "|" << endl;
	cout << "|--------|" << setw(80) << " " << "|--------|" << endl;
	cout << "|" << setw(8) << left << cells[18].getName() << "|" << setw(80) << " " << "|" << setw(8) << left << cells[32].getName() << "|" << endl;	
	cout << "|" << printPlayers(18) << "|" << setw(80) << " " << "|" << printPlayers(32) <<"|" << endl;
	cout << "|        |" << setw(80) << " " << "|        |" << endl;
	cout << "|--------|" << setw(80) << " " << "|--------|" << endl;

	cout << "|" << setw(8) << left << cells[17].getName() << "|" << setw(80) << " " << "|" << setw(8) << left << cells[33].getName() << "|" << endl;	
	cout << "|        |" << setw(80) << " " << "|        |" << endl;
	cout << "|        |" << setw(80) << " " << "|        |" << endl;
	cout << "|" << printPlayers(17) << "|" << setw(80) << " " << "|" << printPlayers(33) <<"|" << endl;
	cout << "|        |" << setw(80) << " " << "|        |" << endl;
	cout << "|--------|" << setw(80) << " " << "|--------|" << endl;

	cout << "|" << setw(8) << printImpr(cells[16].getImpr()) << "|" << setw(80) << " " << "|" << setw(8) << printImpr(cells[34].getImpr()) << "|" << endl;
	cout << "|--------|" << setw(80) << " " << "|--------|" << endl;
	cout << "|" << setw(8) << left << cells[16].getName() << "|" << setw(80) << " " << "|" << setw(8) << left << cells[34].getName() << "|" << endl;	
	cout << "|" << printPlayers(16) << "|" << setw(80) << " " << "|" << printPlayers(34) <<"|" << endl;
	cout << "|        |" << setw(80) << " " << "|        |" << endl;
	cout << "|--------|" << setw(80) << " " << "|--------|" << endl;

	cout << "|" << setw(8) << left << cells[15].getName() << "|" << setw(80) << " " << "|" << setw(8) << left << cells[35].getName() << "|" << endl;	
	cout << "|        |" << setw(80) << " " << "|        |" << endl;
	cout << "|        |" << setw(80) << " " << "|        |" << endl;
	cout << "|" << printPlayers(15) << "|" << setw(80) << " " << "|" << printPlayers(35) <<"|" << endl;
	cout << "|        |" << setw(80) << " " << "|        |" << endl;
	cout << "|--------|" << setw(80) << " " << "|--------|" << endl;


	cout << "|" << setw(8) << printImpr(cells[14].getImpr()) << "|" << setw(80) << " " << "|NEEDLES |" << endl; //for building improvement
	cout << "|--------|" << setw(80) << " " << "|HALL    |" << endl;
	cout << "|" << setw(8) << left << cells[14].getName() << "|" << setw(80) << " " << "|        |" << endl;	
	cout << "|" << printPlayers(14) << "|" << setw(80) << " " << "|" << printPlayers(36) <<"|" << endl;
	cout << "|        |" << setw(80) << " " << "|        |" << endl;
	cout << "|--------|" << setw(80) << " " << "|--------|" <<endl;

	cout << "|" << setw(8) << printImpr(cells[13].getImpr()) << "|" << setw(80) << " " << "|" << setw(8) << printImpr(cells[37].getImpr()) << "|" << endl;
	cout << "|--------|" << setw(80) << " " << "|--------|" << endl;
	cout << "|" << setw(8) << left << cells[13].getName() << "|" << setw(80) << " " << "|" << setw(8) << left << cells[37].getName() << "|" << endl;	
	cout << "|" << printPlayers(13) << "|" << setw(80) << " " << "|" << printPlayers(37) <<"|" << endl;
	cout << "|        |" << setw(80) << " " << "|        |" << endl;
	cout << "|--------|" << setw(80) << " " << "|--------|" << endl;

	cout << "|" << setw(8) << left << cells[12].getName() << "|" << setw(80) << " " << "|COOP    |" << endl;
	cout << "|        |" << setw(80) << " " << "|FEE     |" << endl;
	cout << "|" << printPlayers(12) << "|" << setw(80) << " " << "|" << printPlayers(38) <<"|" << endl;
	cout << "|        |" << setw(80) << " " << "|        |" << endl;
	cout << "|--------|" << setw(80) << " " << "|--------|" << endl;

	//9th property on vertical edge, counting from top
	cout << "|" << setw(8) << printImpr(cells[11].getImpr()) << "|" << setw(80) << " " << "|" << setw(8) << printImpr(cells[39].getImpr()) << "|" << endl;
	cout << "|--------|" << setw(80) << " " << "|--------|" << endl;
	cout << "|" << setw(8) << left << cells[11].getName() << "|" << setw(80) << " " << "|" << setw(8) << left << cells[39].getName() << "|" << endl;	
	cout << "|" << printPlayers(11) << "|" << setw(80) << " " << "|" << printPlayers(39) <<"|" << endl;
	cout << "|        |" << setw(80) << " " << "|        |" << endl;
	cout << "|--------|--------------------------------------------------------------------------------|--------|" <<endl;

	//line 2
	for (int i = 10; i >= 0; --i){
		if (cells[i].getName() == "DC_Tims_Line"){
			cout << "|" <<setw(8)<<left<< "DC Tims" << "" ;
		}else if (cells[i].getName() == "NEEDLES_HALL"){
			cout <<"|" << setw(8) << left <<"NEEDLES";
		}else if(cells[i].getName() == "COLLECT_OSAP"){
			cout <<"|" << setw(8) << left <<"COLLECT" << "|";
		}else if(cells[i].getName() == "MKV" || cells[i].getName() == "TUITION" || cells[i].getName() == "SLC"){
			cout <<"|" << setw(8) << cells[i].getName();
		}else{
			cout << "|" << setw(8) << printImpr(cells[i].getImpr()); //if building has improvemnts add it here...
		}
	}
	cout << endl;

	//line 3
	for (int i = 10; i >= 0; --i){
		if (cells[i].getName() == "DC_Tims_Line"){
			cout << "|" <<setw(8)<< left << "Line" << "" ;
		}else if (cells[i].getName() == "NEEDLES_HALL"){
			cout <<"|" << setw(8) << left << "HALL";
		}else if(cells[i].getName() == "COLLECT_OSAP"){
			cout <<"|" << setw(8) << left << "OSAP"<< "|";
		}else if(cells[i].getName() == "MKV" || cells[i].getName() == "TUITION" || cells[i].getName() == "SLC"){
			cout <<"|        ";
		}else{
			cout << "|--------";
		}
	}
	cout << endl;

	//line 4
	for (int i = 10; i >= 0; --i){
		if (!cells[i].getIsProperty()){
			cout << "|" <<setw(8) << " " ;
			if(cells[i].getName() == "COLLECT_OSAP") cout << "|";
		}else{
			cout << "|" << setw(8) << left << cells[i].getName();
		}
	}
	cout << endl;

	//line 5
	for (int i = 10; i >= 0; --i){
		cout <<"|" << printPlayers(i); //set players here
	}
	cout << "|" <<endl;
	//line 6
	for (int i = 10; i >= 0; --i){
		cout <<"|" << "        "; 
	}
	cout << "|" <<endl;

	//line 7
	cout << "----------------------------------------------------------------------------------------------------" << endl;


}
