#include "toInclude.h"
#include "map.h"
#include <ncurses.h>

using namespace std;


char defaultmap[MAP_HEIGHT+1][MAP_WIDE+1] = 
{
	{"|-----------------------------------------------------------------------------|"},
	{"|                                                                             |"},
	{"| |--------------------------|        |-----------------------|               |"},
	{"| |..........................|        |.......................|               |"},
	{"| |..........................+########+.......................|-------|       |"},
	{"| |..........................|   #    |...............................|--|    |"},
	{"| |..........................|   #    |..................................|--| |"},
	{"| |----------+---------------|   #    |----+----------------|...............| |"},
	{"|            #                 #############                |...............| |"},
	{"|            #                 #     |-----+------|         |...............| |"},
	{"|            #                 #     |............|         |...............| |"},
	{"|            ###################     |............|   ######+...............| |"},
	{"|            #                 #     |............|   #     |...............| |"},
	{"|            #                 #     |-----+------|   #     |--------+------| |"},
	{"|  |---------+-----------|     #           #          #              #        |"},
	{"|  |.....................|     #           #          #         |----+------| |"},
	{"|  |.....................|     ########################         |...........| |"},
	{"|  |.....................|     #           #                    |...........| |"},
	{"|  |.....................|     #    |------+--------------------|...........| |"},
	{"|  |.....................|     #    |.......................................| |"},
	{"|  |.....................+##########+.......................................| |"},
	{"|  |.....................|          |.......................................| |"},
	{"|  |---------------------|          |---------------------------------------| |"},
	{"|                                                                             |"},
	{"|-----------------------------------------------------------------------------|"}
};

Map::Map(){}

void Map::clearMap(){
	for (int i = 0; i < MAP_HEIGHT; i++){
		for (int j = 0; j < MAP_WIDE; j++){
			 MapDisplay[i][j] = ' ';
		}
	}
}

void Map::notify(int column, int row, char update){
	MapDisplay[row][column] = update;
}

void Map::printMap(){
	for (int i = 0; i < MAP_HEIGHT; i++){
		for (int j = 0; j < MAP_WIDE; j++){
			char value = MapDisplay[i][j];
			mvaddch(i,j,value);
		}
		printw("\n");
	}
}
int Map::getValue(int column, int row){
	return MapDisplay[row][column];
}
bool Map::isPassble(int column,int row){
	bool truthFlag = false;
	if (MapDisplay[row][column] == '.' || MapDisplay[row][column] == '#'
		|| MapDisplay[row][column] == '+' || MapDisplay[row][column] == STAIR
		|| MapDisplay[row][column] == GOLD || MapDisplay[row][column] == POTION){
		truthFlag = true;
		return truthFlag;
	}
	return truthFlag;
}
bool Map::isWall(int column,int row){
	bool truthFlag = false;
	if (MapDisplay[row][column] == '-' || MapDisplay[row][column] == '|'
		/*|| MapDisplay[row][column] == HUMAN || MapDisplay[row][column] == DWARF
		|| MapDisplay[row][column] == HALFLING || MapDisplay[row][column] == ORC
		|| MapDisplay[row][column] == ELF || MapDisplay[row][column] == MERCHANT*/){
		truthFlag = true;
		return truthFlag;
	}
	return truthFlag;
}
Map::~Map(){}
