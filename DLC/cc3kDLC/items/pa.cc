#include "pa.h"

using namespace std;

AttackPotion::AttackPotion(Cell *update, bool positive,string name,int type)
:Potion(update,name,type), positive(positive){}
AttackPotion::~AttackPotion(){}

void AttackPotion::effect(Hero *hero){
	int value = AHEFFECT;
	if (hero->getType() == "Drow"){
		value = value * DROWPOTION;
	}
	if (positive){		
		hero->setKnownPotion(type);
		hero->setAtk(-value);
		hero->setAtkBuff(-value);
	}
	else{	
		hero->setKnownPotion(type);
		hero->setAtk(value);
		hero->setAtkBuff(value);
	}
}
