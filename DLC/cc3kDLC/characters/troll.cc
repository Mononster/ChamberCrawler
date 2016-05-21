#include "troll.h"

using namespace std;

Troll::Troll(int atk,int def,int hp, char name) 
:Hero(atk,def,hp,hp,name,0){
				type = "Troll";
}

void Troll::heroSkill(){
	if (this->getHp() < 120){
		this->setHp(-5);
	}
}


