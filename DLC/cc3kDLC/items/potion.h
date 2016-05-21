#ifndef POTION_H
#define POTION_H

#include "item.h"
#include "../characters/hero.h"

class Potion : public Item
{
protected:
	int type;
public:
	Potion(Cell *update , std::string name,int type);
	int getType();
	virtual void effect(Hero *hero) = 0;
	virtual ~Potion() = 0;
};



#endif
