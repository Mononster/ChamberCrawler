#ifndef INVENTORY_H
#define INVENTORY_H

#include "toInclude.h"
#include "../characters/hero.h"


class Inventory
{
	std::vector<Potion *> listofPotions;
	Hero *hero;
public:
	void addPotion(Potion *);
	bool usePotion(int index);
	void setHero(Hero *hero);
	void print();
	void deleteIt();
	Inventory();
	~Inventory();
};



#endif

