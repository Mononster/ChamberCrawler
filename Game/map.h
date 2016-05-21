#ifndef MAP_H
#define MAP_H

#include "toInclude.h"

class Map{
	char MapDisplay[MAP_HEIGHT][MAP_WIDE];
	// 2-Dimensional char array to store the map.
public:
	Map();
	int getValue(int column, int row); // get the state at given position.
	bool isPassble(int column, int row); //check if the position can be walked on.
	bool isWall(int column,int row); // check if the postion is a wall ('|' and '-')
	void notify(int column, int row, char update); // receive update information from controller.
	void printMap(); // simple print the map.
	~Map();
};

#endif

