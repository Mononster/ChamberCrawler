#ifndef Halfling_H
#define Halfling_H

#include "enemy.h"

class Halfling : public Enemy
{
public:
	Halfling(Cell *toRegister,int atk = 20,int def = 30,int hp = 100, char name = HALFLING);
	~Halfling(){}

	/* data */
};

#endif
