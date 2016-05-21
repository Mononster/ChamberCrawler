#ifndef SHADE_H
#define SHADE_H

#include "hero.h"

class Shade : public Hero
{
public:
	Shade(int atk = 25,int def = 25,int hp = 125, char name = HERO);
	~Shade(){}
};


#endif

