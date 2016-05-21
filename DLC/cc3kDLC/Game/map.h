#ifndef MAP_H
#define MAP_H

#include "toInclude.h"

class Map{
	char MapDisplay[MAP_HEIGHT][MAP_WIDE];
public:
	int getValue(int column, int row);
	void printMap();
	void notify();
	void spawnChamber();
	void notify(int column, int row, char update);
	bool isPassble(int column, int row);
	bool isWall(int column,int row);
	void clearMap();
	Map();
	~Map();
};

#endif
