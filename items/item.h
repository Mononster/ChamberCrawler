/* Base class for tresures and potions 
   because both of them are items */

#ifndef ITEM_H
#define ITEM_H

#include "../Game/toInclude.h"
#include "../Game/cell.h"

class Item
{
protected:
	std::string name;
	Cell* itemCell;
public:
	Item(std::string name,Cell *update);
	virtual Cell* getCell() const;
	virtual std::string getName() const; 
	void setCell(Cell *);
	virtual ~Item(){}
};


#endif
