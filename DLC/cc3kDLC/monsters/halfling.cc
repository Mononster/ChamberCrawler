#include "halfling.h"

Halfling::Halfling(Cell *toRegister,int atk,int def,int hp, char name) 
			:Enemy(atk,def,hp,name,toRegister,false){}

			