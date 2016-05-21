#ifndef PD_H
#define PD_H

#include "potion.h"

class DefensePotion : public Potion
{
	bool positive; // if the potion is positive (true for positive, false for negative).
public:
	DefensePotion(Cell *update, bool positive, std::string name, int type);
	void effect(Hero *hero);
	~DefensePotion();
};

#endif
