#include "dragon.h"

Dragon::Dragon(Cell *toRegister,Cell *goldCell,int atk,int def,int hp, char name) 
			:Enemy(atk,def,hp,name,toRegister,false,goldCell){}

bool Dragon::ifGetViolated(Hero *hero){
	for (int i = 0; i < MAXNEIGHBOURS; i++){
		//check if hero is within 1 block radius of dragon hoard.
		Cell *neighbour = goldCell->getNeighbours(i);
		if (neighbour->getPositionX() == hero->getPositionX() && 
			neighbour->getPositionY() == hero->getPositionY()){
			setNeutral(false);
			return true;
		}
	}
	return false;
}

Dragon::~Dragon(){}
