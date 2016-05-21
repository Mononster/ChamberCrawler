#include "inventory.h"
#include "../items/potion.h"

using namespace std;

Inventory::Inventory(): hero(0){}
Inventory::~Inventory(){
	while (listofPotions.size() > 0){
		Potion *toDelete = listofPotions.back();
		listofPotions.pop_back();
		delete toDelete;
	}
	listofPotions.clear();
}


void Inventory::addPotion(Potion * toAdd){
	listofPotions.push_back(toAdd);
}
bool Inventory::usePotion(int index){
	if (index >= listofPotions.size() || index < 0){
		printw("You dont have that much of Potions, try again!\n");
		return false;
	} 
	Potion *toUse = listofPotions.at(index);
	toUse->effect(hero);
	string toOut = "PC uses " + toUse->getName()+  "!";
	printw("%s\n",toOut.c_str());
	//printw("Press any Key to continue");
	listofPotions.erase(listofPotions.begin() + index);
	return true;
}

void Inventory::setHero(Hero *hero){
	this->hero = hero;
}

void Inventory::print(){
	clear();
	printw("Inventory!\n");
	for (int i = 0; i < listofPotions.size();i++){
		bool ifKnown = hero->checkKnown(listofPotions.at(i));
		if (ifKnown){
			printw("%d: %s\n",i,listofPotions.at(i)->getName().c_str());
		}else{
			printw("%d: Unknown Potion.\n",i);
		}
	}
}