/* This file provides the cell class, where each cell is one particular
   element in the game board. 
*/

#ifndef CELL_H
#define CELL_H
#include "toInclude.h"

class Game; // forward declaration of game class, so we dont need to include it and avoid mutually
 			// include.
class Cell{
	Game *game; // the big game class that cell belong to (only one).
	Cell *neighbours[MAXNEIGHBOURS]; // array to store all the neighbours of it.
	int numNeighbours; // record how many neighbours it has.
	int positionX; 
	int positionY;
	char prevState; // previous state.
	char state; // current state.
	bool visited;
public:
	Cell();
	void addNeighbour(Cell *neighbour);//add a neighbouring cell
	void lookUp(); // looking for all neighbours with same state '.'
	 /**** getters and setters *****/
	Cell* getNeighbours(int index) const;
	int getPositionX() const;
	int getPositionY() const;
	char getPrev() const;
	char getState() const ;
	bool getVisited() const;
	void notifyGame() const; 
  	void setState(const char& change);
  	void setPrev(const char& change);
	void setCoords(const int column, const int row); 
	//setter for private co-ordinates of cell
	void setGame(Game * game);  //setter for game
  	void setVisit(bool b);
  	~Cell();
};


#endif

