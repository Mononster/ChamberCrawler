#ifndef Elf_H
#define Elf_H

#include "enemy.h"

class Elf : public Enemy
{
public:
	Elf(Cell *toRegister,int atk = 30,int def = 10,int hp = 140, char name = ELF);
	~Elf(){}
};

#endif
