#include "chamber.h"

using namespace std;

Chamber::Chamber():visible(false){}
Chamber::~Chamber(){}

void Chamber::addCell(Cell *toAdd){
	listofCell.push_back(toAdd);
	/*for (vector<Cell *>::iterator it = listofCell.begin() ; 
			it != listofCell.end(); ++it){
			//cout << "here" << endl;
			cout << (*it)->getState() << endl;
		}*/
	//cout << listofCell.back()->getPositionX()<< " " << listofCell.back()->getPositionY()
	//<< listofCell.back()->getState() <<endl;
}

vector<Cell*> Chamber::getLoCell(){
	return this->listofCell;
}

bool Chamber::getVisible(){
	return visible;
}
void Chamber::setVisible(bool ifVisible){
	visible = ifVisible;
}
