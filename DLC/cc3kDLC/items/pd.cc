#include "pd.h"

using namespace std;

DefensePotion::DefensePotion(Cell *update, bool positive,string name,int type)
:Potion(update,name,type), positive(positive){}

DefensePotion::~DefensePotion(){}

void DefensePotion::effect(Hero *hero){
	int value = DHEFFECT;
	if (hero->getType() == "Drow"){
		value = value * DROWPOTION;
	}
	if (positive){	
		hero->setKnownPotion(type);
		hero->setDef(-value);
		hero->setDefBuff(-value);
	}
	else{	
		hero->setKnownPotion(type);
		hero->setDef(value);
		hero->setDefBuff(value);
	}
}
