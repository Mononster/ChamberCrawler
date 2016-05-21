#include "hero.h"
#include <cmath>
#include "../monsters/enemy.h"
#include "../items/potion.h"

using namespace std;

Hero::Hero(int atk, int def, int hp,int maxHp, char name, Cell* update)
 : Character(atk,def,hp,name,update),gold(100),maxHp(maxHp),atkBuff(0),defBuff(0){
 	for (int i = 0; i< POTION_KIND; i++){
 		knownPotion[i] = -2;
 	}
 	typeKnown = 0;
 }
bool Hero::isDied(){
	if (getHp() <= 0){
		return true;
	}
	return false;
}
string Hero::getType(){
	return type;
}
int Hero::getGold(){
	return gold;
}
int Hero::getMaxHp(){
	return maxHp;
}
int Hero::getAtkBuff(){
	return atkBuff;
}
int Hero::getDefBuff(){
	return defBuff;
}
string Hero::getAction(){
	return action;
}
void Hero::addAction(string actionToAdd){
	action = action +  actionToAdd;
}
bool Hero::checkKnown(Potion *find){
	for (int i = 0; i< POTION_KIND; i++){
		//cout << knownPotion[i] << " " << find->getType() << endl;
		if (find->getType() == knownPotion[i]){

			return true;
		}
	}
	return false;
}

void Hero::addGold(int toAdd){
	gold = gold + toAdd;
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
int Hero::getPositionX(){
	return PositionX;
}
int Hero::getPositionY(){
	return PositionY;
} // getters
void Hero::setPositionX(int x){
	PositionX = x;
}
void Hero::setPositionY(int y){
	PositionY = y;
}
void Hero::setAction(string toModify){
	action = toModify;
}
bool Hero::checkNeighbourEnemy(int posX, int posY){

	for (int i = 0; i < MAXNEIGHBOURS; i++){
		Cell *neigbour = this->characterCell->getNeighbours(i);
		int x = neigbour->getPositionX();
		int y = neigbour->getPositionY();
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

bool Hero::checkNeighbourPotion(int &posX, int &posY){
	for (int i = 0; i < MAXNEIGHBOURS; i++){
		Cell *neigbour = this->characterCell->getNeighbours(i);
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
	if (getType() == "Vampire"){
		setHp(-VAMPIREGAIN);
		if (toFight->getName() == DWARF){
			setHp(VAMPIREGAIN * 2);
		}
	}
	if (toFight->getName() == HALFLING){
		int torand = rand() % 2;
		if (torand == 1){
			setAction("L MISSES PC'S ATTACK!");
			return;
		}
	}
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
	string toOut = "PC deals " + printDamage + " damage to " +  printName + "(" +
		printHp + ")! ";
	setAction(toOut);
	
	/*b = 100.0 + getDef();
	damage = ceil((a/b) * toFight->getAtk());
	setHp(damage);
	ss << damage;
	ss >> printDamage;
	ss.clear();
	ss << getHp();
	ss >> printHp;

	toOut = printName + " deals " + printDamage + " damage to PC(" + printHp + " HP)!";
	addAction(toOut);*/
}




























