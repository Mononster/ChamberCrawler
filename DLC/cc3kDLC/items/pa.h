#ifndef PA_H
#define PA_H

#include "potion.h"

class AttackPotion : public Potion
{
	bool positive;
public:
	AttackPotion(Cell *update, bool positive, std::string name,int type);
	~AttackPotion();
	void effect(Hero *hero);

	/* data */
};

#endif
