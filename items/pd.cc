#include "pd.h"

using namespace std;

DefensePotion::DefensePotion(Cell *update, bool positive,string name,int type)
:Potion(update,name,type), positive(positive){}

void DefensePotion::effect(Hero *hero){
	int value = DHEFFECT;
	//check if hero is Drow, set the effect to 1.5 times.
	if (hero->getType() == "Drow"){
		value = value * DROWPOTION;
	}
	//check if the potion is positive
	if (positive){	
		hero->setKnownPotion(type);
		hero->setDef(-value);
		hero->setDefBuff(-value);
	}
	else{
		//potion effect is negative	
		if (hero->getDef() - value <= 0){
			hero->setDefBuff(hero->getDef());
			hero->setDef(hero->getDef());
			hero->setKnownPotion(type);	
		}
		else{
			hero->setDef(value);
			hero->setDefBuff(value);
			hero->setKnownPotion(type);
		}
		
	}
}

DefensePotion::~DefensePotion(){}
