#ifndef CHARACTER_H
#define CHARACTER_H

#include "../Game/cell.h"

class Character{
	int atk;
	int def;
	int hp;
protected:
	char name;
	Cell* characterCell;
public:
	Character(int atk, int def, int hp, char name, Cell *toResister);
	virtual ~Character();
	int getAtk() const;
	int getDef() const;
	int getHp() const;
	Cell* getCell();
	virtual void setHp(int toSet);
	virtual void setAtk(int atk);
	virtual void setDef(int def);
	virtual void setCell(Cell *toset);
	char getName() const; // getters
};

#endif
