#ifndef DROW_H
#define DROW_H

#include "hero.h"

class Drow : public Hero
{
public:
	Drow(int atk = 20,int def = 30,int hp = 100, char name = HERO);
	~Drow(){}
};


#endif
