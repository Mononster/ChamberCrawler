#ifndef HUMAN_H
#define HUMAN_H

#include "enemy.h"

class Human : public Enemy
{
public:
	Human(Cell *toRegister,int atk = 20,int def = 20,int hp = 140, char name = HUMAN);
	~Human(){}

	/* data */
};

#endif
