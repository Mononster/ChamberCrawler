#ifndef Elf_H
#define Elf_H

#include "enemy.h"

class Elf : public Enemy
{
public:
	Elf(Cell *toRegister,int atk = 20,int def = 30,int hp = 100, char name = ELF);
	~Elf(){}

	/* data */
};

#endif
