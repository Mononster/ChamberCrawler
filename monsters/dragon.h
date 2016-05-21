#ifndef DRAGON_H
#define DRAGON_H

#include "enemy.h"

class Dragon : public Enemy
{
public:
	Dragon(Cell *toRegister,Cell *goldCell,int atk = 20,int def = 20,int hp = 150, 
		char name = DRAGON);
	bool ifGetViolated(Hero *);
	~Dragon();
};  

#endif

