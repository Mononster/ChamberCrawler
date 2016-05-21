#ifndef CELL_H
#define CELL_H
#include "toInclude.h"
class Game; 
class Cell{
	int PositionX;
	int PositionY;
	char state;
	char prevState;
	Cell *neighbours[MAXNEIGHBOURS];
	int numNeighbours;
	int chamberIndex;
	Game *game;
	bool visited;

public:
	Cell();
	~Cell();
	char getState() const ;          //getter for private state
	char getPrev() const;
	bool getVisited() const;
	Cell* getNeighbours(int index);
	int getPositionX() const;
	int getChamberIndex();
	int getPositionY() const;
  	void setState(const char& change);         //setter for private state
  	void setPrev(const char& change);
  	void setChamberIndex(int chamberIndex);

	void setCoords(const int column, const int row); //setter for private co-ordinates of cell
	void setGame(Game * game);  //setter for game
  	void setVisit(bool b);
  	void notifyGame() const;
  	void addNeighbour(Cell *neighbour);       //add a neighbouring cell
  	void lookUp(int chamberNumber); // looking for all neighbours with same state '.'

};

#endif
