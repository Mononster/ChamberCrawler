#ifndef PD_H
#define PD_H

#include "potion.h"

class DefensePotion : public Potion
{
	bool positive;
public:
	DefensePotion(Cell *update, bool positive, std::string name, int type);
	~DefensePotion();
	void effect(Hero *hero);

	/* data */
};

#endif
