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
	virtual Cell* getCell();
	void setCell(Cell *);
	virtual ~Item(){}
	virtual std::string getName();
	/* data */
};


#endif
