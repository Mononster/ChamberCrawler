#ifndef VAMPIRE_H
#define VAMPIRE_H

#include "hero.h"

class Vampire : public Hero
{
public:
	Vampire(int atk = 25, int def = 500, int hp = 500, char name = HERO);
	~Vampire(){}
};


#endif

