#ifndef Orc_H
#define Orc_H

#include "enemy.h"

class Orc : public Enemy
{
public:
	Orc(Cell *toRegister,int atk = 30,int def = 25,int hp = 180, char name = ORC);
	~Orc(){}
};

#endif

