#include "ph.h"

using namespace std;

HealthPotion::HealthPotion(Cell *update, bool positive,string name,int type)
:Potion(update,name,type), positive(positive){}

HealthPotion::~HealthPotion(){}

void HealthPotion::effect(Hero *hero){
	int value = AHEFFECT;
	if (hero->getType() == "Drow"){
		value = value * DROWPOTION;
	}
	if (positive){			
		hero->setKnownPotion(type);
		if (hero->getHp() + value > hero->getMaxHp()){
			int toset = hero->getMaxHp() - hero->getHp();
			hero->setHp(-toset);
		}
		else{
			hero->setHp(-value);
		}
	}
	else{	
		hero->setKnownPotion(type);
		if (hero->getHp() - value < 0){
			int toset = hero->getHp() - 0;
			hero->setHp(toset);
		}
		else{
			hero->setHp(value);
		}
	}

}
