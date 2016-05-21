#ifndef Orc_H
#define Orc_H

#include "enemy.h"

class Orc : public Enemy
{
public:
	Orc(Cell *toRegister,int atk = 20,int def = 30,int hp = 100, char name = ORC);
	~Orc(){}

	/* data */
};

#endif
