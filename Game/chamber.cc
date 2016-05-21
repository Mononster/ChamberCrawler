#include "chamber.h"

using namespace std;

Chamber::Chamber(){}

void Chamber::addCell(Cell *toAdd){
	listofCell.push_back(toAdd);
}

vector<Cell*> Chamber::getLoCell(){
	return this->listofCell;
}

Chamber::~Chamber(){}
