/* MOST IMPORTANT CLASS IN THIS PROJECT, DEAL WITH ALL KINDS OF 
   GENERATION, PRINT INFO AND COMBAT.
*/

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

/*
 * Abstract class to allow Game to send noticiations to a registered object
 */
class GameNotification {
  public:
    virtual void notify(int column, int row, char state) = 0;
};

class Game{
	Cell **board; // game board, two dimensional Cell objects array.
	Chamber *listofChambers[MAX_CHAMBERS]; //List of Rooms in the game.
	Hero *hero;
	GameNotification *gameNotification; // register controller to game object.
	std::vector<Enemy *> listofEnemies; // all enemies.
	std::vector<Potion *> listofPotions; // all potions.
	std::vector<Tresure *> listofTresures; // all tresures.

	int chamberNumber;
	int dragons; // record how many dragons in the game.
	int floorLevel; // record floor level.
	int heroChamber; 
	// record the chamber that hero spawned
	// (in order to make stair generate in different chamber than hero's).
	bool merchantNeutral; 
	// in order to update neutral property to all the merchant in enemies vector.
public:
	Game();
	void bossRegisterGold(); // register a gold to a neighbour dragon(only work if files are provided).
	void change(int column,int row, char state); // change cell state.
	bool checkWin(); // if reach 5, win.
	void clearFloor(); // delete all the things in previous floor, because hero cant get back to previous floor.
	void fillChamber(); // find all cell with '.' that in a chamber and update to the list.
	void fillChamber(Cell *toAdd); // update to chamberlist;
	Potion* findPotion(int x, int y,bool flag); //return a potion at {x,y}.
	Tresure* findTresure(int x, int y); // return a tresure(gold) at {x,y}.
	int findValue(int x, int y); // check value of the gold.
	void generate(); //generate everything.	
	void generateHero();
	void generateStair();
	void generateEnemy();
	void generateItems(); // generate tresures and potions.
	Cell getCell(int column, int row); 
	int getFloorLevel(); 
	std::vector<Enemy *> getListofEnemies();
	bool heroAttack(int x, int y); // return true if enemy died
	void init(int column, int row, char state); // init cell objects to the game.
	void init(GameNotification *gameNotification,Hero *hero); // register gamenotification -> connected controller.
	void notify(int column, int row, char state); // notify gameNotification.
	void moveEnemy();
	void printInfo();
	Cell* randAndReplace(int &); // random choose a cell in a chamberlist.
	void setFloorLevel();
	~Game();
};



#endif 
