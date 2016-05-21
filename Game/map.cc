#include "toInclude.h"
#include "map.h"

using namespace std;

Map::Map(){}

int Map::getValue(int column, int row){
	return MapDisplay[row][column];
}

bool Map::isPassble(int column,int row){
	// all the elements that the hero can walk on.
	if (MapDisplay[row][column] == '.' || MapDisplay[row][column] == '#'
		|| MapDisplay[row][column] == '+' || MapDisplay[row][column] == STAIR
		|| MapDisplay[row][column] == GOLD){
		return true;
	}
	return false;
}

bool Map::isWall(int column,int row){
	if (MapDisplay[row][column] == '-' || MapDisplay[row][column] == '|'){
		return true;
	}
	return false;
}

void Map::notify(int column, int row, char update){
	MapDisplay[row][column] = update;
}

void Map::printMap(){
	for (int i = 0; i < MAP_HEIGHT; i++){
		for (int j = 0; j < MAP_WIDE; j++){
			char value = MapDisplay[i][j];
			cout << value;
		}
		cout << endl;
	}
}

Map::~Map(){}
