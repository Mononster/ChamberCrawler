#include "ph.h"

using namespace std;

HealthPotion::HealthPotion(Cell *update, bool positive,string name,int type)
:Potion(update,name,type), positive(positive){}

void HealthPotion::effect(Hero *hero){
	int value = PHEFFECT;
	//check if hero is Drow, set the effect to 1.5 times.
	if (hero->getType() == "Drow"){
		value = value * DROWPOTION;
	}
	//check if the potion effect is positive
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
		//potion effect is negative
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

HealthPotion::~HealthPotion(){}
