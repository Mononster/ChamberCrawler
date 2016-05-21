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
bool Enemy::getNeutral(){
	return neutral;
}
Cell *Enemy::getGoldCell(){
	return goldCell;
}
void Enemy::setGoldCell(Cell *goldCell){
	this->goldCell = goldCell;
}

void Enemy::combat(Hero *hero){
	int ifMiss = rand()% MISS_RATE;
	stringstream ss;
	string printName;
	ss << name;
	ss >> printName;
	ss.clear();
	if (ifMiss == 0){
		string toOut = printName + " tries to attack PC, however PC MISSED IT!";
		hero->addAction(toOut);
	}
	if (ifMiss == 1){
		float a = 100.0;
		float b = 100.0+hero->getDef();
		float damage = ceil((a/b) * getAtk());
		//cout << damage << endl;	
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
    	hero->getType() + "(" + printHp + " HP)!";
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
	//bool randMove = false;
	//cout << name << " ";
	while (!succGenerate && !haveEnemy && record < MAXNEIGHBOURS){
		int index = rand() % MAXNEIGHBOURS;
		for (int i = 0; i< MAXNEIGHBOURS; i++){
			//cout << characterCell->getNeighbours(i)->getState();
			posX = characterCell->getNeighbours(i)->getPositionX();
			posY = characterCell->getNeighbours(i)->getPositionY();
			if (neutral == false && posX == hero->getPositionX() &&
			 posY == hero->getPositionY()){
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
			neighbourCell->getPositionY()!= hero->getPositionY()){
			//cout << "here" << endl;
			setCell(characterCell->getNeighbours(index));
			succGenerate = true;
		}
		record++;
	}
	if (haveEnemy == true){
		haveEnemy = false;
		return 't';
	}
	type = name;
	return type;

}
