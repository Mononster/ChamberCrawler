#include "pa.h"

using namespace std;

AttackPotion::AttackPotion(Cell *update, bool positive,string name,int type)
:Potion(update,name,type), positive(positive){}

void AttackPotion::effect(Hero *hero){
	int value = AHEFFECT;
	//check if the hero is Drow, set the effect to 1.5 tiems.
	if (hero->getType() == "Drow"){
		value = value * DROWPOTION;
	}
	//check if the Potion is positive
	if (positive){		
		hero->setKnownPotion(type);
		hero->setAtk(-value);
		hero->setAtkBuff(-value);
	}
	else{	
		//Potion is a negative Potion.
		if (hero->getAtk() - value <= 0){
			hero->setAtkBuff(hero->getAtk());
			hero->setAtk(hero->getAtk());
			hero->setKnownPotion(type);	
		}
		else{
			hero->setAtk(value);
			hero->setAtkBuff(value);
			hero->setKnownPotion(type);
		}
		
	}
}
AttackPotion::~AttackPotion(){}
