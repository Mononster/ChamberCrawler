#ifndef GAME_H
#define GAME_H

#include "toInclude.h"
#include "cell.h"
#include "chamber.h"
#include "../characters/hero.h"
#include "../monsters/enemy.h"
#include "../monsters/human.h"
#include "../monsters/dwarf.h"
#include "../monsters/halfling.h"
#include "../monsters/elf.h"
#include "../monsters/orc.h"
#include "../monsters/merchant.h"
#include "../monsters/dragon.h"
#include "../items/tresure.h"
#include "../items/item.h"
#include "includePotion.h"
#include "../characters/shade.h"
#include "../characters/drow.h"
#include "../characters/goblin.h"
#include "../characters/vampire.h"
#include "../characters/troll.h"
#include "inventory.h"
/*
 * Abstract class to allow Game to send noticiations to a registered object
 */
class GameNotification {
  public:
    virtual void notify(int column, int row, char state) = 0;
};

class Game{
	Cell **board;
	Hero *hero;
	Inventory *inventory;
	Chamber *listofChambers[MAX_CHAMBERS];
	GameNotification *gameNotification;
	std::vector<Enemy *> listofEnemies;
	std::vector<Tresure *> listofTresures;
	std::vector<Potion *> listofPotions;
	int chamberNumber;
	int heroChamber;
	int floorLevel;
	bool merchantNeutral;


public:
	Game();
	~Game();
	Cell getCell(int column, int row);
	std::vector<Enemy *> getListofEnemies();
	void clearFloor();
	void setFloorLevel();
	void init(int column, int row, char state); // init cell objects to the game.
	void notify(int column, int row, char state, int chamberIndex); // notify gameNotification.
	void notify(int index);
	void init(GameNotification *gameNotification,Hero *hero); // register gamenotification -> connected controller.
	void fillChamber(); // find all cell with '.' that in a chamber and update to the list.
	void fillChamber(Cell *toAdd); // update to chamberlist;
	void print();
	void printInfo();
	void bossRegisterGold();
	void generateHero();
	void generateStair();
	void generateEnemy();
	void generateItems();
	Inventory* getInventory();
	int getFloorLevel();
	void change(int column,int row, char state);
	void generate(int a); //generate everything.	
	bool checkWin();
	Cell* randAndReplace(int &);
	Cell* helpGenerateEnemy(int &posX, int &posY);
	void moveEnemy();
	bool heroAttack(int x, int y); // return true if enemy died
	int findValue(int x, int y);
	Tresure* findTresure(int x, int y);
	Potion* findPotion(int x, int y,bool flag);
	void buyFromMerchant(char command);
	int searchChamber(int x, int y);
};



#endif 
