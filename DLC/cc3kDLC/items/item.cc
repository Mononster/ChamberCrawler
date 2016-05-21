#include "item.h"

using namespace std;

Item::Item(string name, Cell * update) : name(name),itemCell(update){}
Cell* Item::getCell(){
	return itemCell;
}

void Item::setCell(Cell* toSet){
	itemCell = toSet;
}

string Item::getName(){
	return name;
}
