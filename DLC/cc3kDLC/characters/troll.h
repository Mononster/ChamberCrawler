#ifndef TROLL_H
#define TROLL_H

#include "hero.h"

class Troll : public Hero
{
public:
	void heroSkill();
	Troll(int atk = 25, int def = 15, int hp = 120, char name = HERO);
	~Troll(){}
};


#endif
