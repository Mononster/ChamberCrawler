#ifndef ENEMY_H
#define ENEMY_H

#include "../Game/toInclude.h"
#include "../characters/character.h"
#include "../Game/cell.h"
#include "../characters/hero.h"



class Enemy : public Character
{
	bool neutral;
protected:
	Cell* goldCell;
public:
	Enemy(int atk, int def, int hp, char name,Cell *toRegister,bool neutral,Cell *goldCell = 0);
	char move(Hero *hero, int times);
	void setNeutral(bool toset);
	bool getNeutral() const;
	void combat(Hero*);
	Cell* getGoldCell() const;
	void setGoldCell(Cell *goldCell);
	virtual bool ifGetViolated(Hero *);
	virtual ~Enemy(){}
};

#endif

