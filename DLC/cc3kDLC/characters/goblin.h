#ifndef GOBLIN_H
#define GOBLIN_H

#include "hero.h"

class Goblin : public Hero
{
public:
	Goblin(int atk = 15, int def = 20, int hp = 110, char name = HERO);
	~Goblin(){}
};


#endif
