/* Every chamber is a collection of cells.
   Basically chamber class help us generate
   all kinds of staff in the game to be more
   fairly. i.e. Bigger chamber will not have 
   more game elements than smaller chamber.*/

#ifndef CHAMBER_H
#define CHAMBER_H

#include "toInclude.h"
#include "cell.h"

class Chamber{

	std::vector<Cell *> listofCell;
	// a list to store all the cell inside this chamber.
public:
	Chamber();
	void addCell(Cell *toAdd); // add a cell to the chamber.
	std::vector<Cell *> getLoCell(); // getter for the list.
	~Chamber();

};


#endif 

