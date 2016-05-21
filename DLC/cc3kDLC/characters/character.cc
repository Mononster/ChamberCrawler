#include "character.h"

using namespace std;

Character::Character(int atk, int def, int hp, char name, Cell *update)
:atk(atk),def(def), hp(hp), name(name) ,characterCell(update){}

Character::~Character(){}

Cell* Character::getCell(){
	return characterCell;
}

int Character::getAtk() const{
	return atk;
}
int Character::getDef() const{
	return def;
}
int Character::getHp() const{
	return hp;
}
void Character::setHp(int toSet){
	hp = hp - toSet;
}
void Character::setAtk(int atk){
	this->atk = this->atk - atk;
}
void Character::setDef(int def){
	this->def = this->def - def;
}
void Character::setCell(Cell *toset){
	characterCell = toset;
}
char Character::getName() const{
	return name;
}

