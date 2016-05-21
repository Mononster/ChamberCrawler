#include "potion.h"

using namespace std;

Potion::Potion(Cell* update,string name,int type) : 
Item(name,update),type(type){}

int Potion::getType() const{
	return type;
}

void Potion::effect(Hero *hero){}

Potion::~Potion(){}

