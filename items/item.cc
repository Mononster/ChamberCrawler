#include "item.h"

using namespace std;

Item::Item(string name, Cell * update) : name(name),itemCell(update){}

Cell* Item::getCell() const{
	return itemCell;
}

string Item::getName() const{
	return name;
}

void Item::setCell(Cell* toSet){
	itemCell = toSet;
}
