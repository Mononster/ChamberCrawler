#ifndef PH_H
#define PH_H

#include "potion.h"

class HealthPotion : public Potion
{
	bool positive;
public:
	HealthPotion(Cell *update, bool positive, std::string name,int type);
	~HealthPotion();
	void effect(Hero *hero);

	/* data */
};

#endif
