#include "game.h"


using namespace std;


Game::Game() : board(0),chamberNumber(0),floorLevel(0),merchantNeutral(true){
	inventory = new Inventory();
}
Game::~Game(){
	delete inventory;
	clearFloor();
}
int Game::searchChamber(int x, int y){
	for (int i = 0; i < chamberNumber; i++){
		for (int j = 0; j < listofChambers[i]->getLoCell().size(); j++){
			int posx = listofChambers[i]->getLoCell().at(j)->getPositionX();
			int posy = listofChambers[i]->getLoCell().at(j)->getPositionY();
			if (x == posx && y == posy){
				return i;
			}
		}
	}
	return -1;
}

void Game::clearFloor(){
	if (board != 0){
		for (int i = 0; i < chamberNumber; i++){
			delete listofChambers[i];
		}
		for (int i = 0; i < MAP_HEIGHT; i++){
			delete [] board[i];
		}
		delete [] board;
		while (listofEnemies.size() > 0){
			Enemy *toDelete = listofEnemies.back();
			listofEnemies.pop_back();
			delete toDelete;
		}
		listofEnemies.clear();
		while (listofTresures.size() > 0){
			Item *toDelete = listofTresures.back();
			listofTresures.pop_back();
			delete toDelete;
		}
		listofTresures.clear();
		listofPotions.clear();
		chamberNumber = 0;
		hero->setAtk(hero->getAtkBuff());
		hero->setDef(hero->getDefBuff());
		hero->setAtkBuff(0);
		hero->setDefBuff(0);
	}

}
int Game::getFloorLevel(){
	return floorLevel;
}
Cell Game::getCell(int column, int row){
	return board[row][column];
}
vector<Enemy *> Game::getListofEnemies(){
	return listofEnemies;
}

Inventory* Game::getInventory(){
	return inventory;
}


bool Game::checkWin(){
	if (floorLevel == 5){
		return true;
	}
	return false;
}

void Game::setFloorLevel(){
	floorLevel++;
}
void Game::bossRegisterGold(){
	for (int i = 0; i< listofEnemies.size(); i++){
		if (listofEnemies.at(i)->getName() == DRAGON){
			Cell *toLookup = listofEnemies.at(i)->getCell();
			for (int j = 0; j< MAXNEIGHBOURS; j++){
				Cell *myNeighbour = toLookup->getNeighbours(j);
				if (myNeighbour->getState() == GOLD){
					myNeighbour->setPrev(GOLD);
					//printw( "register?" );
					listofEnemies.at(i)->setGoldCell(myNeighbour);
					break;
				}
			}
		}
	}
}
void Game::init(int column, int row, char state){
	Enemy *enemyToGenerate = 0;
	Tresure *gold = 0;
	Potion *potion = 0;
	Cell *normal = &board[row][column];
	char record = state;
	if (state == HERO){
		hero->setPositionX(column);
		hero->setPositionY(row);
		hero->setCell(normal);
	}else if(state == DWARF){
		enemyToGenerate = new Dwarf(normal);
	}else if (state == HUMAN){
		enemyToGenerate = new Human(normal);
	}else if (state == HALFLING){
		enemyToGenerate = new Halfling(normal);
	}else if (state == ELF){
		enemyToGenerate = new Elf(normal);
	}else if (state == ORC){
		enemyToGenerate = new Orc(normal);
	}else if (state == MERCHANT){
		enemyToGenerate = new Merchant(normal);
		if (merchantNeutral == false){
			enemyToGenerate->setNeutral(false);
		}
	}else if (state == DRAGON){
		enemyToGenerate = new Dragon(normal,normal);
	}else if (state == '0'){
		potion = new HealthPotion(normal,true,"RH",0);
	}else if (state == '1'){
		potion = new AttackPotion(normal,true,"BA",1);
	}else if (state == '2'){
		potion = new DefensePotion(normal,true,"BD",2);
	}else if (state == '3'){
		potion = new HealthPotion(normal,false,"PH",3);
	}else if (state == '4'){
		potion = new AttackPotion(normal,false,"WA",4);
	}else if (state == '5'){
		potion = new DefensePotion(normal,false,"WD",5);
	}else if (state == '6'){
		gold = new Tresure(NORMALGOLD,normal);
	}else if (state == '7'){
		gold = new Tresure(SMALLGOLD,normal);
	}else if (state == '8'){
		gold = new Tresure(MERCHANT_HOARD,normal);
	}else if (state == '9'){
		gold = new Tresure(DRAGONGOLD,normal);
		gold->setProtected(true);
	}
	if (enemyToGenerate != 0){
		listofEnemies.push_back(enemyToGenerate);
		record = state;
	}
	if (potion != 0){
		listofPotions.push_back(potion);
		record = POTION;
	}
	if (gold != 0){
		listofTresures.push_back(gold);
		record = GOLD;
	}
	normal->setState(record);
	if (state != HERO){
		normal->setPrev(record);
	}
	if (state == HERO){
		normal->setPrev('.');
	}
	this->change(column,row,record);
	//printw( "here " << record );
}

void Game::notify(int column, int row, char state ,int chamberIndex){
	if (chamberIndex != -1){
		if (listofChambers[chamberIndex]->getVisible() == true ||
			chamberIndex == -2 || chamberIndex == -3){ // -2 for passway, -3 for door
			gameNotification->notify(column,row,state);
		}
	}
}
void Game::notify(int index){
	for (int i = 0; i< listofChambers[index]->getLoCell().size() ;i++){
		listofChambers[index]->setVisible(true);
		Cell *toNotify = listofChambers[index]->getLoCell().at(i);
		gameNotification->notify(toNotify->getPositionX(),
			toNotify->getPositionY(),toNotify->getState());
	}
}

void Game::change(int column, int row, char state){
	char prev = board[row][column].getState();
	board[row][column].setPrev(prev);
	if (state == 'c'){
		board[row][column].setPrev(GOLD);
		hero->setCell(&board[row][column]);
		this->notify(column,row,HERO,board[row][column].getChamberIndex());
		return;
	}
	if (state != HERO){
		board[row][column].setState(state);
	}
	if (state == HERO){
		hero->setCell(&board[row][column]);
		this->notify(column,row,state,-2);
		return;
	}
	this->notify(column,row,state,board[row][column].getChamberIndex());
}

void Game::init(GameNotification *gameNotification, Hero *hero){
	clearFloor();
	heroChamber = -1;
	this->gameNotification = gameNotification;
	this->hero = hero;
	this->inventory->setHero(hero);
	board = new Cell*[MAP_HEIGHT];
	for (int i = 0; i < MAP_HEIGHT; i++){
		board[i] = new Cell[MAP_WIDE];
		for (int j = 0; j < MAP_WIDE; j++){
			board[i][j].setGame(this);
			board[i][j].setCoords(j,i);
			board[i][j].setState('.');
			board[i][j].setVisit(false);
			board[i][j].setChamberIndex(-1);
		}
	}
	for (int i = 0; i < MAP_HEIGHT; i++){
		for (int j = 0; j < MAP_WIDE; j++){
			if (i + 1 < MAP_HEIGHT){
				board[i][j].addNeighbour(&board[i+1][j]);
				if (j + 1 < MAP_WIDE){
					board[i][j].addNeighbour(&board[i+1][j+1]);
				}
				if (j - 1 >= 0){
					board[i][j].addNeighbour(&board[i+1][j-1]);
				}
			}
			if (i - 1 >= 0){
				board[i][j].addNeighbour(&board[i-1][j]);
				if (j + 1 < MAP_WIDE){
					board[i][j].addNeighbour(&board[i-1][j+1]);
				}
				if (j - 1 >= 0){
					board[i][j].addNeighbour(&board[i-1][j-1]);
				}
			}
			if (j + 1 < MAP_WIDE){
				board[i][j].addNeighbour(&board[i][j+1]);
			}
			if (j - 1 >= 0){
				board[i][j].addNeighbour(&board[i][j-1]);
			}
		}
	}
}
void Game::fillChamber(Cell *toAdd){
	listofChambers[chamberNumber]->addCell(toAdd);
}

void Game::fillChamber(){
	for (int i = 1; i < MAP_HEIGHT -1; i++){	
		for (int j = 1; j < MAP_WIDE-1; j++){
			if ((board[i][j].getState() == '.' 
				|| board[i][j].getState() == '-'
				|| board[i][j].getState() == '|' 
				|| board[i][j].getState() == '+')
				&& board[i][j].getVisited() == false){
				//printw("%d\n", chamberNumber );
				listofChambers[chamberNumber] = new Chamber();
				board[i][j].lookUp(chamberNumber);
				chamberNumber++;
			}
		}
	}	
	for (int i = 0; i< chamberNumber ; i++){
		int size = listofChambers[i]->getLoCell().size();
		for (int j = 0; j< size; j++){
			listofChambers[i]->getLoCell().at(j)->setVisit(false);
		}
	}
}
void Game::generateHero(){
	Cell *heroCell = randAndReplace(heroChamber);
	listofChambers[heroChamber]->setVisible(TRUE);
	int posX = heroCell->getPositionX();
	int posY = heroCell->getPositionY();
	hero->setPositionX(posX);
	hero->setPositionY(posY);
	hero->setCell(heroCell);
	//printw( "Hero " << posX << " " << posY ); 
	//this->change(posX,posY,HERO);
}

void Game::generateStair(){
	int a = 10;
	Cell *stairCell = randAndReplace(a);
	int posX = stairCell->getPositionX();
	int posY = stairCell->getPositionY();
	//printw( "stair " << posX << " " << posY ); 
	this->change(posX,posY,STAIR);
}
Cell* Game::helpGenerateEnemy(int &posX, int &posY){
	int a = 0;
	Cell* returnCell = randAndReplace(a);
	posY = returnCell->getPositionY();
	posX = returnCell->getPositionX();
	return returnCell;
}
void Game::generateEnemy(){ 
	int size = listofEnemies.size();
	int posX;
	int posY;
	int a = 0;
	char generateType;
	while (size < ENEMY_SIZE){	
		Enemy* enemyToGenerate;
		Cell* enemy = randAndReplace(a);
		int type = rand() % 18;
		if (type < 4){
			enemyToGenerate = new Human(enemy);
			generateType = HUMAN;
		}
		else if (type >= 4 && type < 7){
			enemyToGenerate = new Dwarf(enemy);
			generateType = DWARF;
		}
		else if(type >= 7 && type < 12){
			enemyToGenerate = new Halfling(enemy);
			generateType = HALFLING;
		}
		else if (type >= 12 && type < 14){
			enemyToGenerate = new Elf(enemy);
			generateType = ELF;
		}
		else if (type >= 14 && type < 16){
			enemyToGenerate = new Orc(enemy);
			generateType = ORC;
		}
		else if (type >= 16 && type < 18){
			enemyToGenerate = new Merchant(enemy);
			if (merchantNeutral == false){
				enemyToGenerate->setNeutral(false);
			}
			generateType = MERCHANT;
		}
		listofEnemies.push_back(enemyToGenerate);
		size++;
		posX = enemy->getPositionX();
		posY = enemy->getPositionY();
		this->change(posX,posY,generateType);
	}
}

void Game::generateItems(){
	int a = 0;
	int size = 0;
	int posX;
	int posY;
	bool succGenerate = false;
	while (size < GOLD_SIZE){
		Cell *normal = randAndReplace(a);
		Tresure *Gold;
		int type = rand()% 8;
		if (type < 5){
			Gold = new Tresure(NORMALGOLD,normal);
		}
		else if (type >= 5 && type < 7){
			Gold = new Tresure(SMALLGOLD,normal);
		}
		else if (type == 7){
			Gold = new Tresure(DRAGONGOLD,normal);		
			Cell *toRegister = 0;
			while(!succGenerate){
				int index = rand()% MAXNEIGHBOURS;
				if (normal->getNeighbours(index)->getState() == '.'){
					toRegister = normal->getNeighbours(index);
					break; //missing one condition if gold is full of things.
				}
			}
			normal->setState(GOLD);
			Enemy* dragon = new Dragon(toRegister,normal);
			listofEnemies.push_back(dragon);
			this->change(toRegister->getPositionX(),toRegister->getPositionY(),DRAGON);
			Gold->setProtected(true);
		}
		posX = normal->getPositionX();
		posY = normal->getPositionY();
		listofTresures.push_back(Gold);
		//printw( "Gold " << posX << " " << posY ); 
		this->change(posX,posY,GOLD);	
		size++;
	}
	size = 0;
	while (size < POTION_SIZE){
		Cell *normal = randAndReplace(a);
		Potion *potion;
		int type = rand()% POTION_KIND;
		if (type == 0) potion = new HealthPotion(normal,true,"RH",type);
		if (type == 1) potion = new HealthPotion(normal,false,"PH",type);
		if (type == 2) potion = new AttackPotion(normal,true,"BA",type);
		if (type == 3) potion = new AttackPotion(normal,false,"WA",type);
		if (type == 4) potion = new DefensePotion(normal,true,"BD",type);
		if (type == 5) potion = new DefensePotion(normal,false,"WD",type);
		posX = normal->getPositionX();
		posY = normal->getPositionY();
		listofPotions.push_back(potion);
		this->change(posX,posY,POTION);	
		size++;
	}
}

Cell* Game::randAndReplace(int &indexToMutate){
	int chamberIndex = rand()% chamberNumber;
	Cell *toReturn;
	bool succGenerate = false;
	if (indexToMutate == 10){
		succGenerate = false;
		while (!succGenerate){
			chamberIndex = rand()%chamberNumber;
			if (chamberIndex != heroChamber){
				succGenerate = true;
			}
		}
	}	
	succGenerate = false;
	while (!succGenerate){	
		int cellIndex = rand()%listofChambers[chamberIndex]->getLoCell().size();
		toReturn = listofChambers[chamberIndex]->getLoCell().at(cellIndex);
		if (toReturn->getState() != '.') continue;
		bool visitOrNot = toReturn->getVisited();
		//printw( visitOrNot );
		if (visitOrNot == false){
			listofChambers[chamberIndex]->getLoCell().at(cellIndex)->setVisit(true);
			succGenerate = true;
		}
	}
	indexToMutate = chamberIndex;
	return toReturn;
}
void Game::printInfo(){
	string type = hero->getType();
	printw( "Race: %s Gold: %d\n",type.c_str(),hero->getGold());
	printw( "                                                                       Floor: %d\n", floorLevel);
	printw( "Hp: %d\n", hero->getHp() );
	printw( "Atk: %d\n", hero->getAtk() );
	printw( "Def: %d\n",hero->getDef() );
	printw( "Action: %s\n", hero->getAction().c_str() );
	printw("\n");
	//printw( "Command Options: 'a<direction>' for attacking the enemy in specified direction." ); 
//	printw( "                 'u<direction>' for using the potion in spcified direction." );
//	printw( "                  no,so,ea,we,ne,nw,se,sw represents different directions." );
//	printw( "                 'r' for restarting the game, press 'q' to quit the game." );
//	printw("\n");
	// cannot pass object of non-POD type 'std::string' (aka 'basic_string<char, char_traits<char>, allocator<char> >') through variadic function; call will abort at runtime [-Wnon-pod-varargs]printw( "What command would you like to enter?      Command = " );
}
void Game::generate(int a){
	if (a == 1){
		generateHero();
    	generateStair();
    	generateItems();
    	generateEnemy();
    	notify(heroChamber);
    	this->change(hero->getPositionX(),hero->getPositionY(),HERO);
    	return;
    }
    generateItems();
    generateEnemy();
    heroChamber = searchChamber(hero->getPositionX(),hero->getPositionY());
    if (a != 1){
   	 hero->getCell()->setPrev('.');
   	}
	listofChambers[heroChamber]->setVisible(TRUE);
    notify(heroChamber);
}

void Game::moveEnemy(){
	int posX;
	int posY;
	for (int i = 0 ; i < listofEnemies.size();i++){
		if (listofEnemies.at(i)->getCell()->getState() == DRAGON){
			bool ifAttack = listofEnemies.at(i)->ifGetViolated(hero);
			if (ifAttack){
				listofEnemies.at(i)->combat(hero);
				listofEnemies.at(i)->setNeutral(false);
				continue;
			}else{
				listofEnemies.at(i)->move(hero,1);
				continue;
			}
		}
		posX = listofEnemies.at(i)->getCell()->getPositionX();
		posY = listofEnemies.at(i)->getCell()->getPositionY();
		char type = listofEnemies.at(i)->move(hero,0);
		
		if (type != 't') { // if hero is around enemy.
			this->change(posX,posY,'.');
			posX = listofEnemies.at(i)->getCell()->getPositionX();
			posY = listofEnemies.at(i)->getCell()->getPositionY();
			this->change(posX,posY,type);
		}
		 // check after move.
	}
}
int Game::findValue(int x, int y){
	int value = 0;
	for (int i = 0; i< listofTresures.size(); i++){
		Cell* goldCell = listofTresures.at(i)->getCell();
		if(goldCell->getPositionX() == x &&
			goldCell->getPositionY() == y){
			value = listofTresures.at(i)->getValue();
			goldCell->setState('.');
			break;
		}
	}
	return value;
}
Tresure* Game::findTresure(int x, int y){
	Tresure* reTresure = 0;
	for (int i = 0; i< listofTresures.size(); i++){
		Cell* goldCell = listofTresures.at(i)->getCell();
		reTresure = listofTresures.at(i);
		if(goldCell->getPositionX() == x && goldCell->getPositionY() == y){
			return reTresure;
		}
	}
	return reTresure;
}
Potion* Game::findPotion(int x, int y, bool flag){
	Potion* toReturn = 0;
	for (int i = 0; i< listofPotions.size(); i++){
		Cell* potionCell = listofPotions.at(i)->getCell();
		if(potionCell->getPositionX() == x &&
			potionCell->getPositionY() == y){
			toReturn = listofPotions.at(i);
			if(flag == true){
				potionCell->setState('.');
				inventory->addPotion(toReturn); // add potion to inventory.
			}
			break;
		}
	}

	return toReturn;
}
bool Game::heroAttack(int x, int y){
	for (int i = 0; i< listofEnemies.size(); i++){
		int posX = listofEnemies.at(i)->getCell()->getPositionX();
		int posY = listofEnemies.at(i)->getCell()->getPositionY();
		if (posY == y && posX == x){
			hero->fightEnemy(listofEnemies.at(i));
			if (listofEnemies.at(i)->getName() == MERCHANT){
				for (int j = 0; j < listofEnemies.size(); j++){
					if (listofEnemies.at(j)->getName() == MERCHANT){
						listofEnemies.at(j)->setNeutral(false);
						merchantNeutral = false;
					}
				}
			}
			if (listofEnemies.at(i)->getName() == DRAGON){
				listofEnemies.at(i)->setNeutral(false);
			}
			if (listofEnemies.at(i)->getHp() <= 0){
				if (hero->getType() == "Goblin"){
					hero->addGold(GOBLINGOLD);
				}
				Tresure *dropGold;
				Cell *enemy = listofEnemies.at(i)->getCell();
				if (listofEnemies.at(i)->getName() == HUMAN){
					dropGold = new Tresure(NORMALGOLD*2, enemy);
					this->change(posX,posY,GOLD);
					listofTresures.push_back(dropGold);
				}
				if (listofEnemies.at(i)->getName() == MERCHANT){
					dropGold = new Tresure(MERCHANT_HOARD, enemy);
					this->change(posX,posY,GOLD);
					listofTresures.push_back(dropGold);
				}
				if (listofEnemies.at(i)->getName() == DWARF ||
					listofEnemies.at(i)->getName() == HALFLING){
					hero->addGold(SMALLGOLD);
					this->change(posX,posY,'.');
				}
				if (listofEnemies.at(i)->getName() == ELF || 
					listofEnemies.at(i)->getName() == ORC ){
					hero->addGold(NORMALGOLD);
					this->change(posX,posY,'.');
				}
				if (listofEnemies.at(i)->getName() == DRAGON){
					int x = listofEnemies.at(i)->getGoldCell()->getPositionX();
					int y = listofEnemies.at(i)->getGoldCell()->getPositionY();
					Tresure *locate = findTresure(x,y);
					locate->setProtected(false);
					this->change(posX,posY,'.');
				}
				Enemy *toDelete = listofEnemies.at(i);
				listofEnemies.erase(listofEnemies.begin() + i);
				delete toDelete;			
				return true;
			}
		}
	}
	return false;
}

void Game::buyFromMerchant(char command){
		if (hero->getGold() < 25){
  			printw("Sorry you dont have enough money, press 'q' to quit!\n");
  			return;
  		}
  		if (command == 'z'){	
  			hero->setHp(-100);
  			hero->addGold(-25);
  			printw("Ok, you now improved your Health! %d Hp now! \n",hero->getHp());
  		}else if (command == 'x'){
  			hero->setDef(-8);
  			hero->addGold(-25);
  			printw("Ok, you now improved your Defense! %d Def now! \n", hero->getDef());
  		}else if (command == 'c'){
  			hero->setAtk(-8);
  			hero->addGold(-25);
  			printw("Ok, you now improved your Attack! %d Atk now! \n", hero->getAtk());
  		}else{
  			printw("Wrong Command, try again!\n");
  		}
  		
	
  	//printw("Press any Key to continue");
}









