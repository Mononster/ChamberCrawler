#include "enemy.h"
#include <cmath>

using namespace std;

Enemy::Enemy(int atk, int def, int hp, char name,Cell *toRegister,bool neutral,Cell *goldCell) 
: Character(atk,def,hp,name,toRegister) {
	characterCell = toRegister;
	this->neutral = neutral;
	this->goldCell = goldCell;
}
void Enemy::setNeutral(bool toset){
	neutral = toset;
}
bool Enemy::getNeutral() const{
	return neutral;
}
Cell *Enemy::getGoldCell() const{
	return goldCell;
}
void Enemy::setGoldCell(Cell *goldCell){
	this->goldCell = goldCell;
}
bool Enemy::ifGetViolated(Hero *){
	return true;
}

void Enemy::combat(Hero *hero){
	int ifMiss = rand()% MISS_RATE;
	stringstream ss;
	string printName;
	ss << name;
	ss >> printName;
	ss.clear();
	if (ifMiss==0){
		//calculate damage to hero
		float a = 100.0;
		float b = 100.0+hero->getDef();
		float damage = ceil((a/b) * getAtk());
		if (getName() == ORC && hero->getType() == "Goblin"){
			damage = ceil(damage * 1.5);
		}	
		hero->setHp(damage);	
		string printDamage;
		string printHp;			
		ss << damage;
		ss >> printDamage;
		ss.clear();
		ss << hero->getHp();
		ss >> printHp;						
		string toOut = printName + " deals " + printDamage + " damage to " + 
    	hero->getType() + "(" + printHp + " HP)!\n";
		hero->addAction(toOut);
	} else if (ifMiss == 1){
		string toOut = printName + " tries to attack PC, however PC MISSED IT!\n";
		hero->addAction(toOut);
	}
}
char Enemy::move(Hero *hero,int times){
	bool succGenerate = false;
	char type = '\0';
	int posX;
	int posY;
	int record = 0;
	int atkTimes = 0;
	bool haveEnemy = false;
	//loop through all the neighbours of hero
	while (!succGenerate && !haveEnemy && record < MAXNEIGHBOURS){
		int index = rand() % MAXNEIGHBOURS;
		for (int i = 0; i< MAXNEIGHBOURS; i++){
			posX = characterCell->getNeighbours(i)->getPositionX();
			posY = characterCell->getNeighbours(i)->getPositionY();
			//check if is within one block radius of enemy
			if (neutral == false && posX == hero->getPositionX() &&
			 posY == hero->getPositionY()){
			 	//attack twice to hero when myself is Elf and hero is nor Drow
			 	if (getName() == ELF && hero->getType() != "Drow"){
			 		atkTimes = -1;
			 	}
				while (atkTimes < 1){
					atkTimes++;
					combat(hero);
				}
				haveEnemy = true;
				break;
			}
		}
		Cell *neighbourCell = characterCell->getNeighbours(index);
		if (times == 0 && haveEnemy == false && 
			neighbourCell->getState() == '.'
			&& neighbourCell->getPositionX()!= hero->getPositionX() && 
			neighbourCell->getPositionY()!= hero->getPositionY()) {
			setCell(characterCell->getNeighbours(index));
			succGenerate = true;
		}
		record++;
	}
	//reset the value
	if (haveEnemy == true){
		haveEnemy = false;
		return 't';
	}
	//returns coresponding message.
	type = name;
	return type;
}

