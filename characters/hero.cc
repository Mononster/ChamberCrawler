#include "hero.h"
#include <cmath>
#include "../monsters/enemy.h"
#include "../items/potion.h"

using namespace std;

Hero::Hero(int atk, int def, int hp,int maxHp, char name, Cell* update)
 : Character(atk,def,hp,name,update),atkBuff(0),defBuff(0),gold(0),maxHp(maxHp){
 	for (int i = 0; i< POTION_KIND; i++){
 		knownPotion[i] = -2;
 	}
 	typeKnown = 0;
 }

void Hero::addAction(string actionToAdd){
	action = action +  actionToAdd;
}

void Hero::addGold(int toAdd){
	gold = gold + toAdd;
}

bool Hero::checkKnown(Potion *find) const{
	for (int i = 0; i< POTION_KIND; i++){
		//check if the poison has been used
		if (find->getType() == knownPotion[i]){
			return true;
		}
	}
	return false;
}

bool Hero::checkNeighbourEnemy(int posX, int posY) const{
	for (int i = 0; i < MAXNEIGHBOURS; i++){
		Cell *neigbour = this->characterCell->getNeighbours(i);
		int x = neigbour->getPositionX();
		int y = neigbour->getPositionY();
		//if any of the neibour of hero is enemy return true
		if (posX == x && posY == y && 
			(neigbour->getState() == HUMAN||
			 neigbour->getState() == DWARF||
			 neigbour->getState() == HALFLING||
			 neigbour->getState() == ORC||
			 neigbour->getState() == ELF||
			 neigbour->getState() == MERCHANT||
			 neigbour->getState() == DRAGON)){
			return true;
		}
	}
	return false;
}

bool Hero::checkNeighbourPotion(int &posX, int &posY) const{
	for (int i = 0; i < MAXNEIGHBOURS; i++){
		Cell *neigbour = this->characterCell->getNeighbours(i);
		//check if there is a poison as our neighbour
		if (neigbour->getState() == POTION){
			posX = neigbour->getPositionX();
			posY = neigbour->getPositionY();
			return true;
		}
	}
	return false;
}

void Hero::fightEnemy(Enemy *toFight){
	stringstream ss;
	string printDamage;
	string printName;
	string printHp;
	//if hero is Vampire
	if (getType() == "Vampire"){
		setHp(-VAMPIREGAIN);
		if (toFight->getName() == DWARF){
			setHp(VAMPIREGAIN * 2);
		}
	}
	//if hero is halfling
	if (toFight->getName() == HALFLING){
		int torand = rand() % 2;
		if (torand == 1){
			setAction("L MISSES PC'S ATTACK!");
			return;
		}
	}
	//calculated damage to enemy
	float a = 100.0;
	float b = 100.0 + toFight->getDef();
	float damage = ceil((a/b) * getAtk());
	toFight->setHp(damage);
	ss << damage;
	ss >> printDamage;
	ss.clear();
	ss << toFight->getName();
	ss >> printName;
	ss.clear();
	ss << toFight->getHp();
	ss >> printHp;
	ss.clear();
	printHp = printHp + " HP";
	if (toFight->getHp() < 0){
		printHp = "died";
	}
	//set the prints out damage message.
	string toOut = "PC deals " + printDamage + " damage to " +  printName + "(" +
		printHp + ")! ";
	setAction(toOut);
}

string Hero::getAction() const{
	return action;
}

int Hero::getAtkBuff() const{
	return atkBuff;
}

int Hero::getDefBuff() const{
	return defBuff;
}

int Hero::getGold() const{
	return gold;
}
int Hero::getMaxHp() const{
	return maxHp;
}

int Hero::getPositionX() const{
	return PositionX;
}
int Hero::getPositionY() const{
	return PositionY;
}

string Hero::getType() const{
	return type;
}

bool Hero::isDied() const{
	if (getHp() <= 0){
		return true;
	}
	return false;
}

void Hero::setAction(string toModify){
	action = toModify;
}

void Hero::setAtkBuff(int buff){
	atkBuff = atkBuff - buff;
}

void Hero::setDefBuff(int buff){
	defBuff = defBuff - buff;
}

void Hero::setKnownPotion(int potion){
	knownPotion[typeKnown] = potion;
	typeKnown++;
}

void Hero::setPositionX(int x){
	PositionX = x;
}
void Hero::setPositionY(int y){
	PositionY = y;
}
