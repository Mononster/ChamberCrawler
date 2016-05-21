#ifndef PH_H
#define PH_H

#include "potion.h"

class HealthPotion : public Potion
{
	bool positive; // if the potion is positive (true for positive, false for negative).
public:
	HealthPotion(Cell *update, bool positive, std::string name,int type);
	void effect(Hero *hero);
	~HealthPotion();
};

#endif
