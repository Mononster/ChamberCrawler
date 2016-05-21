#include "potion.h"

using namespace std;

Potion::Potion(Cell* update,string name,int type) : 
Item(name,update),type(type){}

int Potion::getType(){
	return type;
}

void Potion::effect(Hero *hero){}

Potion::~Potion(){}

