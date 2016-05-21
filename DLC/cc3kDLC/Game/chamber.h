#ifndef CHAMBER_H
#define CHAMBER_H

#include "toInclude.h"
#include "cell.h"

class Chamber{

std::vector<Cell *> listofCell;
bool visible;
public:
	Chamber();
	~Chamber();
	std::vector<Cell *> getLoCell();
	void addCell(Cell *toAdd);
	bool getVisible();
	void setVisible(bool ifVisible);

};


#endif 
