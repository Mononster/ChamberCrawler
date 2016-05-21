#include "game.h"
using namespace std;


Game::Game() : board(0),chamberNumber(0),floorLevel(0),merchantNeutral(true){}

void Game::bossRegisterGold(){
	for (unsigned int i = 0; i< listofEnemies.size(); i++){
		if (listofEnemies.at(i)->getName() == DRAGON){ 
			// search dragon first.
			Cell *toLookup = listofEnemies.at(i)->getCell();
			for (int j = 0; j< MAXNEIGHBOURS; j++){
				// looking for a cell with state gold in neighbours.
				Cell *myNeighbour = toLookup->getNeighbours(j);
				if (myNeighbour->getState() == GOLD){
					myNeighbour->setPrev(GOLD);
					// update the dragon hoard to the dragon object.
					listofEnemies.at(i)->setGoldCell(myNeighbour);
					break;
				}
			}
		}
	}
}
void Game::change(int column, int row, char state){
	// change the cell state with the provided one
	// update prev state to original state.
	// if the state is HERO, we do not change the state
	// to the cell.
	char prev = board[row][column].getState();
	board[row][column].setPrev(prev);
	if (state == 'c'){
		// speicial case for dragon hoard.
		// we do not want to change the state of
		// the gold if the gold hasnt be picked up.
		board[row][column].setPrev(GOLD);
		hero->setCell(&board[row][column]);
		this->notify(column,row,HERO);
		return;
	}
	if (state != HERO){
		board[row][column].setState(state);
	}
	if (state == HERO){
		hero->setCell(&board[row][column]);
	}
	this->notify(column,row,state);
}

bool Game::checkWin(){
	if (floorLevel == 5){
		return true;
	}
	return false;
}

void Game::clearFloor(){
	if (board != 0){
		for (int i = 0; i < MAX_CHAMBERS; i++){
			delete listofChambers[i];
		} // clear chamberlist.
		for (int i = 0; i < MAP_HEIGHT; i++){
			delete [] board[i];
		}
		delete [] board;
		// clear board
		while (listofEnemies.size() > 0){
			Enemy *toDelete = listofEnemies.back();
			listofEnemies.pop_back();
			delete toDelete;
		}
		// clear enemies.
		listofEnemies.clear();
		while (listofTresures.size() > 0){
			Item *toDelete = listofTresures.back();
			listofTresures.pop_back();
			delete toDelete;
		}
		// clear tresures and potions.
		listofTresures.clear();
		while (listofPotions.size() > 0){
			Item *toDelete = listofPotions.back();
			listofPotions.pop_back();
			delete toDelete;
		}
		listofPotions.clear();
		chamberNumber = 0;
		hero->setAtk(hero->getAtkBuff());
		hero->setDef(hero->getDefBuff());
		//update hero atk and def.
		hero->setAtkBuff(0);
		hero->setDefBuff(0);
	}

}

void Game::fillChamber(){
	for (int i = 0; i < MAP_HEIGHT; i++){
		for (int j = 0; j < MAP_WIDE; j++){
			// if the state of the cell is '.' and the cell has not been visited.
			// we create a new chamber, and loop throgh all the neighbours of the cell
			// to add them to this chamber.
			if (board[i][j].getState() == '.' && board[i][j].getVisited() == false){
				listofChambers[chamberNumber] = new Chamber();
				board[i][j].lookUp();
				chamberNumber++;
			}
		}
	}
	// set all cells in their corresponding chamber to be not visted
	// which to help us generate game elements later.
	for (int i = 0; i< MAX_CHAMBERS ; i++){
		int size = listofChambers[i]->getLoCell().size();
		for (int j = 0; j< size; j++){
			listofChambers[i]->getLoCell().at(j)->setVisit(false);
		}
	}
}
 
void Game::fillChamber(Cell *toAdd){
	// add the cell to corresponding chamber.
	listofChambers[chamberNumber]->addCell(toAdd);
}

Potion* Game::findPotion(int x, int y, bool flag){
	// we ensure in controller that x,y in the map definatelly 
	// is a potion.
	Potion* toReturn = 0;
	for (unsigned int i = 0; i< listofPotions.size(); i++){
		Cell* potionCell = listofPotions.at(i)->getCell();
		// find in the potion list.
		if(potionCell->getPositionX() == x &&
			potionCell->getPositionY() == y){
			toReturn = listofPotions.at(i);
			if(flag == true){
				potionCell->setState('.');
			}
			break;
		}
	}
	return toReturn;
}

/* following methods behave as same as findPotion */
int Game::findValue(int x, int y){
	int value = 0;
	for (unsigned int i = 0; i< listofTresures.size(); i++){
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
	for (unsigned int i = 0; i< listofTresures.size(); i++){
		Cell* goldCell = listofTresures.at(i)->getCell();
		reTresure = listofTresures.at(i);
		if(goldCell->getPositionX() == x && goldCell->getPositionY() == y){
			return reTresure;
		}
	}
	return reTresure;
}
/*Random generation parts start.
	* random probabilities of an enemy generation.
        1    Human:      2/9
        2    Dwarf:      3/18
        3    Halfling:   5/18
        4    Elf:        1/9
        5    Orc:        1/9
        6    Merchant:   1/9

    * probabilities of a gold generation.
        1    Normal:     5/8
        2    Small:      1/4
        3    Dragon:     1/8
	
	* probabilities for all potions generation = 1/6
*/

void Game::generateHero(){
	Cell *heroCell = randAndReplace(heroChamber);
	// randomly choose a cell in chamber list.
	int posX = heroCell->getPositionX();
	int posY = heroCell->getPositionY();
	hero->setPositionX(posX);
	hero->setPositionY(posY);
	hero->setCell(heroCell);
	this->change(posX,posY,HERO);
}

void Game::generateStair(){
	int a = 10;
	Cell *stairCell = randAndReplace(a);
	int posX = stairCell->getPositionX();
	int posY = stairCell->getPositionY();
	this->change(posX,posY,STAIR);
}

void Game::generateEnemy(){ 
	int size = listofEnemies.size() - dragons;
	// enemies size do not count in dragons.
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
	while (size < POTION_SIZE){
                Cell *normal = randAndReplace(a);
                Potion *potion;
                int type = rand()% POTION_KIND;
                //............................Positive or negative, name, type integer.
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
	size = 0;
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
			// if a dragon hoard is generated, a dragon is generated.
			dragons++;		
			Cell *toRegister = 0;
			while(!succGenerate){
				// loop through all the neighbours beside the hoard to find
				// a place with state '.' and add a dragon on it.
				int index = rand()% MAXNEIGHBOURS;
				if (normal->getNeighbours(index)->getState() == '.'){
					toRegister = normal->getNeighbours(index);
					break;
				}
			}
			normal->setState(GOLD);
			// register the goldcell to the dragon.
			Enemy* dragon = new Dragon(toRegister,normal);
			listofEnemies.push_back(dragon);
			this->change(toRegister->getPositionX(),toRegister->getPositionY(),DRAGON);
			Gold->setProtected(true);
		}
		posX = normal->getPositionX();
		posY = normal->getPositionY();
		listofTresures.push_back(Gold);
		this->change(posX,posY,GOLD);	
		size++;
	}
}

Cell Game::getCell(int column, int row){
	return board[row][column];
}

int Game::getFloorLevel(){
	return floorLevel;
}

std::vector<Enemy *> Game::getListofEnemies(){
	return listofEnemies;
}

void Game::setFloorLevel(){
	floorLevel++;
}

void Game::init(int column, int row, char state){
	Enemy *enemyToGenerate = 0;
	Tresure *gold = 0;
	Potion *potion = 0;
	dragons = 0;
	Cell *normal = &board[row][column];
	char record = state;
	//generate coresponding state for initialization in the gameboard
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
		dragons++;
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
	this->notify(column,row,record);
}

void Game::notify(int column, int row, char state){
	gameNotification->notify(column,row,state);
}



void Game::init(GameNotification *gameNotification, Hero *hero){
	clearFloor();
	heroChamber = -1;
	this->gameNotification = gameNotification;
	this->hero = hero;
	board = new Cell*[MAP_HEIGHT];
	for (int i = 0; i < MAP_HEIGHT; i++){
		board[i] = new Cell[MAP_WIDE];
		for (int j = 0; j < MAP_WIDE; j++){
			board[i][j].setGame(this);
			board[i][j].setCoords(j,i);
			board[i][j].setState('.');
			board[i][j].setVisit(false);
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



Cell* Game::randAndReplace(int &indexToMutate){
	int chamberIndex = rand()% MAX_CHAMBERS;
	Cell *toReturn;
	bool succGenerate = false;
	if (indexToMutate == 10){
		succGenerate = false;
		while (!succGenerate){
			chamberIndex = rand()%MAX_CHAMBERS;
			if (chamberIndex != heroChamber){
				succGenerate = true;
			}
		}
	}	
	succGenerate = false;
	while (!succGenerate){	
		int cellIndex = rand()%listofChambers[chamberIndex]->getLoCell().size();
		toReturn = listofChambers[chamberIndex]->getLoCell().at(cellIndex);
		bool visitOrNot = toReturn->getVisited();
		if (visitOrNot == false){
			listofChambers[chamberIndex]->getLoCell().at(cellIndex)->setVisit(true);
			succGenerate = true;
		}
	}
	indexToMutate = chamberIndex;
	return toReturn;
}

void Game::printInfo(){
	cout << "Race: " << hero->getType() << " Gold: " << hero->getGold();
	cout << "                                                  Floor: " << floorLevel<< endl;
	cout << "Hp: " << hero->getHp() << endl;
	cout << "Atk: " << hero->getAtk() << endl;
	cout << "Def: " <<hero->getDef() << endl;
	cout << "Action: \n"<< hero->getAction() << endl;
	cout << endl;
	cout << "Command Options: 'a<direction>' for attacking the enemy in specified direction." << endl; 
	cout << "                 'u<direction>' for using the potion in spcified direction." << endl;
	cout << "                  no,so,ea,we,ne,nw,se,sw represents different directions." << endl;
	cout << "                 'r' for restarting the game, press 'q' to quit the game." << endl;
	cout << endl;
	cout << "What command would you like to enter?      Command = ";
}

void Game::generate(){
	generateHero();
    generateStair();
    generateItems();
    generateEnemy();
}

void Game::moveEnemy(){
	int posX;
	int posY;
	for (unsigned int i = 0 ; i < listofEnemies.size();i++){
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


bool Game::heroAttack(int x, int y){
	for (unsigned int i = 0; i< listofEnemies.size(); i++){
		int posX = listofEnemies.at(i)->getCell()->getPositionX();
		int posY = listofEnemies.at(i)->getCell()->getPositionY();
		if (posY == y && posX == x){
			hero->fightEnemy(listofEnemies.at(i));
			if (listofEnemies.at(i)->getName() == MERCHANT){
				for (unsigned int j = 0; j < listofEnemies.size(); j++){
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
				string name;
				stringstream ss;
				ss << listofEnemies.at(i)->getName();
				ss >> name;
				string toOut = " Enemy " + name + 
				" has been slained.\n";
				hero->addAction(toOut);

				Enemy *toDelete = listofEnemies.at(i);
				listofEnemies.erase(listofEnemies.begin() + i);
				delete toDelete;		
				
				return true;
			}
		}
	}
	return false;
}

Game::~Game(){
	clearFloor();
}





