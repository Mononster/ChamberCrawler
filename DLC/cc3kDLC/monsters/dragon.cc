#include "dragon.h"

Dragon::Dragon(Cell *toRegister,Cell *goldCell,int atk,int def,int hp, char name) 
			:Enemy(atk,def,hp,name,toRegister,true,goldCell){}

bool Dragon::ifGetViolated(Hero *hero){
	for (int i = 0; i < MAXNEIGHBOURS; i++){
		Cell *neighbour = goldCell->getNeighbours(i);
		if (neighbour->getPositionX() == hero->getPositionX() && 
			neighbour->getPositionY() == hero->getPositionY()){
			setNeutral(false);
			return true;
		}
	}
	return false;
}

