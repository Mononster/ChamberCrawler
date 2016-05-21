#ifndef DWARF_H
#define DWARF_H

#include "enemy.h"

class Dwarf : public Enemy
{
public:
	Dwarf(Cell *toRegister,int atk = 20,int def = 30,int hp = 100, 
		char name = DWARF);
	~Dwarf(){}
};  

#endif

