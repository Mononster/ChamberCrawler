#ifndef HERO_H
#define HERO_H

#include "character.h"

class Potion;
class Enemy;

class Hero : public Character{
	int PositionX;
	int PositionY;
	int gold;
	int maxHp;
	int atkBuff;
	int defBuff;
	int knownPotion[POTION_KIND];
	int typeKnown;
	std::string action;
protected:
	std::string type;
public:
	std::string getType();
	int getMaxHp();
	int getGold();
	int getAtkBuff();
	int getDefBuff();
	std::string getAction();
	void setKnownPotion(int);
	void setAtkBuff(int buff);
	void setDefBuff(int buff);
	void addGold(int toAdd);
	int getPositionX();
	int getPositionY(); // getters
	void setPositionX(int x);
	void setPositionY(int y); // setters
	void setAction(std::string);
	void addAction(std::string);
	bool checkNeighbourEnemy(int posX, int posY);
	bool checkNeighbourPotion(int &posX, int &posY);
    void fightEnemy(Enemy *toFight);
    bool checkKnown(Potion *);
    bool isDied();
	Hero(int atk, int def, int hp,int maxHp, char name,Cell* update);
	virtual void heroSkill(){}
	virtual ~Hero(){}
};

/*class Elf : public Hero{
public:
	Elf(int atk ,int def,int hp, std::string name = "Elf"):Hero(atk,def,hp,name){}
};*/
#endif
	