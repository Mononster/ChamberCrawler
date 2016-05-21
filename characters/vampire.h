#ifndef VAMPIRE_H
#define VAMPIRE_H

#include "hero.h"

class Vampire : public Hero
{
public:
	Vampire(int atk = 25, int def = 25, int hp = 50, char name = HERO);
	~Vampire(){}
};


#endif

