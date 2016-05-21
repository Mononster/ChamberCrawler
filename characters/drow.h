#ifndef DROW_H
#define DROW_H

#include "hero.h"

class Drow : public Hero
{
public:
	Drow(int atk = 25,int def = 15,int hp = 150, char name = HERO);
	~Drow(){}
};


#endif

