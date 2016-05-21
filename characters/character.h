/* base class for enemies and heros */

#ifndef CHARACTER_H
#define CHARACTER_H

#include "../Game/cell.h"

class Character{
	int atk;
	int def;
	int hp;
protected:
	Cell* characterCell;
	char name;
public:
	Character(int atk, int def, int hp, char name, Cell *toResister);
	int getAtk() const;
	Cell* getCell() const;
	int getDef() const;
	int getHp() const;
	char getName() const; 
	virtual void setHp(int toSet);
	virtual void setAtk(int atk);
	virtual void setDef(int def);
	virtual void setCell(Cell *toset);
	virtual ~Character();
};

#endif
