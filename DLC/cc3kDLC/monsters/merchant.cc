#include "merchant.h"

Merchant::Merchant(Cell *toRegister,int atk,int def,int hp, char name) 
			:Enemy(atk,def,hp,name,toRegister,true){}
			