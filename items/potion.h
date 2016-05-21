/* Pure abstract base class for all kinds of potions. */


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
	virtual void effect(Hero *hero) = 0;
	int getType() const;
	virtual ~Potion() = 0;
};



#endif
