/*****************************************************
   This file provides the base class for all different
   kinds of heros in this game and Hero class is also 
   a sub-class of character. 
******************************************************/

#ifndef HERO_H
#define HERO_H

#include "character.h"

class Potion;
class Enemy;

class Hero : public Character{
	std::string action;  // for prting out hero's different actions
	int atkBuff; // record the effects potions have brought to the hero.
	int defBuff; // so we could get hero's orgin atk when they going to other floors.
	int gold;    // how many golds they held.
	int knownPotion[POTION_KIND]; // an array to record if the player has already taken this potion.
	int maxHp; 	 
	int PositionX;
	int PositionY;
	int typeKnown; 
protected:
	std::string type; // hero's type.
public:
	Hero(int atk, int def, int hp,int maxHp, char name,Cell* update);
	void addAction(std::string); // modify actions.
	void addGold(int toAdd);
	bool checkKnown(Potion *) const;   // check if players knew this particular potion.
	bool checkNeighbourEnemy(int posX, int posY) const;  // check if there are enemies beside hero.
	bool checkNeighbourPotion(int &posX, int &posY) const; // check if there are potions beside hero.
	void fightEnemy(Enemy *toFight); // hero attacks enemies.
	std::string getAction() const; 
	int getAtkBuff() const;
	int getDefBuff() const;
	int getGold() const;
	int getMaxHp() const;
	int getPositionX() const;
	int getPositionY() const; // getters
	std::string getType() const; // get hero's race.
	virtual void heroSkill(){} // hero's special skill depending on the race.
	bool isDied() const; 
	void setAction(std::string);
	void setAtkBuff(int buff);
	void setDefBuff(int buff);
	void setKnownPotion(int);
	void setPositionX(int x);
	void setPositionY(int y); // setters
	virtual ~Hero(){}
};

#endif

	