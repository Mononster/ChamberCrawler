#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "toInclude.h"
#include "../characters/hero.h"
#include "map.h"
#include "game.h"

class Controller : public GameNotification
{
	int fileRow; // help read from a file.
	Game *game;
	Hero *hero;
	Map *map;
	bool stayFloor; // check if hero is in the current floor.
	
public:
	Controller();

	bool checkGold(int x, int y) const;// check if {x,y} is a gold.
	bool checkPotion(int x, int y) const; // check if {x,y} is a potion.
	bool checkStair(int x, int y) const; // check if {x,y} is a stair.
	void decideDirection(std::string move,int &x, int &y); 
	// pass in a string move, to trans it to a 2D position (mutate x and y).
	bool decideRace(); // if finishing choosing race return true.
	bool fight(std::string direction); // hero fight enemy at direction.
	void init(Game &g, std::string filename = "defaultLevel.txt"); // init the game, read from 'filename.txt'.
	void move(int &posX, int &posY,std::string direction);//for character moving
	void notify(int column, int row, char update); // notify map to change graphical character.
	bool play(std::string filename,int &); // main controlller function.
	void seePotion(); //check if there is a potion beside hero.
	~Controller(); 

};


#endif
