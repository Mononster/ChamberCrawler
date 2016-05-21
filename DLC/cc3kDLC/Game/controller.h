#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "toInclude.h"
#include "map.h"
#include "game.h"

class Controller : public GameNotification
{
	Map *map;
	Hero *hero;
	Game *game;
	bool stayFloor;
	int fileRow;
public:
	
	bool play(std::string filename,int &);
	void notify(int column, int row, char update);
	void init(Game &g, std::string filename);
	bool checkStair(int x, int y);
	bool checkGold(int x, int y);
	bool checkPotion(int x, int y);
	bool checkEnemy(int x, int y);
	bool checkAtkDirection(std::string move);
	void move(int &posX, int &posY,std::string direction);//for character moving
	std::string convertMove(int move);
	void decideDirection(std::string move,int &x, int &y);
	bool decideRace();
	void fight(std::string direction);
	void seePotion();
	bool checkMerchant(int x, int y);
	void buy();
	void showPassWay(Cell *cell);
	void showDoor(Cell *cell);
	Controller();
	~Controller();
};




#endif
