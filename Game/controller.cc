#include "controller.h"

using namespace std;

bool ifValid(string direction){ // simply check if the given direction is valid.
	if((direction == "no") || direction == "ea" || direction == "we" || direction =="so"
		||direction == "nw" || direction == "sw" || direction == "ne" || direction == "se"){
		return true;
	}
	return false;
}

Controller::Controller(){
  game = new Game();
  map = NULL;
  hero = NULL;
  fileRow = 0; // start from 0 line in the file.
}

bool Controller::checkGold(int x, int y) const{
	if (map->getValue(x,y) == GOLD){
		return true;
	}
	return false;
}

bool Controller::checkPotion(int x, int y) const{
	if (map->getValue(x,y) == POTION){
		return true;
	}
	return false;
}

bool Controller::checkStair(int x, int y) const{
	if (map->getValue(x,y) == STAIR){
		return true;
	}
	return false;
}

void Controller::decideDirection(string direction,int &x, int &y){
	int recordX = x; // if the direction is wall, let x and y be origin values.
	int recordY = y;
	if (direction == "no"){
		x = hero->getPositionX();
		y = hero->getPositionY()-1;
		hero->setAction("PC moves North ");
	}else if (direction == "so"){
		x = hero->getPositionX();
		y = hero->getPositionY()+1;
		hero->setAction("PC moves South ");
	}else if (direction == "ea"){
		x = hero->getPositionX()+1;
		y = hero->getPositionY();
		hero->setAction("PC moves East ");
	}else if (direction == "we"){
		x = hero->getPositionX()-1;
		y = hero->getPositionY();
		hero->setAction("PC moves West ");
	}else if (direction == "nw"){
		x = hero->getPositionX()-1;
		y = hero->getPositionY()-1;
		hero->setAction("PC moves NorthWest ");
	}else if (direction == "ne"){
		x = hero->getPositionX()+1;
		y = hero->getPositionY()-1;
		hero->setAction("PC moves NorthEast ");
	}else if (direction == "se"){
		x = hero->getPositionX()+1;
		y = hero->getPositionY()+1;
		hero->setAction("PC moves SouthEast ");
	}else if (direction == "sw"){
		x = hero->getPositionX()-1;
		y = hero->getPositionY()+1;
		hero->setAction("PC moves SouthWest ");
	}
	if (!map->isWall(x,y)){
		return;
	}else{
		x = recordX;
		y = recordY;
	}
}

bool Controller::decideRace(){
	char race;
	cin >> race;
	switch(race){
		case 's' : 
		hero = new Shade();
		break;
		case 'd' :
		hero = new Drow();
		break;
		case 't' :
		hero = new Troll();
		break;
		case 'v' :
		hero = new Vampire();
		break;
		case 'g' :
		hero = new Goblin();
		break;
		default:
		return false;
	}
	return true;
}

bool Controller::fight(string direction){
	bool hasEnemy = false;
	int x = 0;
	int y = 0;
	decideDirection(direction,x,y);
	hasEnemy = hero->checkNeighbourEnemy(x,y);
	 // check if there is an enemy beside hero.
	if (hasEnemy){
		// if there is, let hero attack it and return true.
		game->heroAttack(x,y);
		return true;
	}
	else {
		return false;
	}
}



void Controller::init(Game &g, string filename){
    ifstream file(filename.c_str());
	*game = g; // resgister game.
	string input;
	char record;
	int length;
	int row = 0; // record which rows are we read in.
	int beginFile = 1; // skip the lines that we do not want.
	
	while(getline(file,input)){	
		if (beginFile <= fileRow - 1){
			beginFile++;
			continue;
		}
		length = input.length();
		for (int column = 0; column < length; column++){
			record = input[column];
			game->init(column,row,record);
		}
		row++;
		if (row > MAP_HEIGHT-1) break;
	}
	if (filename != "defaultLevel.txt"){
		fileRow = MAP_HEIGHT * (game->getFloorLevel()+1) +1;
	} // if no file provided, we dont have to update filerow.
}



void Controller::move(int &posX, int &posY,string move){
	int recordX = posX;
	int recordY = posY;
	decideDirection(move,posX,posY); // get x and y by given move.
	if (checkPotion(posX,posY)){
		posX = recordX;
		posY = recordY;
		hero->setAction("Woops, thats a potion, you can not walk on it. Press 'u' to use it.");
		return;
	} // first check if x, y is a potion.
	if (map->isPassble(posX, posY)){
		char lastPos = game->getCell(recordX,recordY).getPrev(); 
		// get the prev state of a cell, so we can mutate back to the origin state after hero walked on it.
		char pos = HERO;
		if (checkStair(posX, posY)){
			stayFloor = false;
		} // if x,y is a stair, then we move to next floor.
		if (checkGold(posX,posY)){
			int value = game->findValue(posX,posY); 
			// get the value of the gold first.
			bool protectd = game->findTresure(posX,posY)->getProtected();
			// check if the gold is a dragon hoard.
			if (!protectd){ // if not, picks it.
				string printValue;
				stringstream ss;
				ss << value;
				ss >> printValue;
				hero->addGold(value);
				string toOut = "and picks up " + printValue + " gold!";
				hero->addAction(toOut);
				game->findTresure(posX,posY)->getCell()->setState('.');
			}
			else if(protectd){
				pos = 'c'; 
				// pass 'c' to game->change method, which has special way to deal with it.
			}
		}
		hero->setPositionX(posX);
		hero->setPositionY(posY);
		game->change(recordX,recordY,lastPos);
		game->change(posX,posY,pos);
		game->moveEnemy();	// after move hero, move enemies.
		return;
	}
	if (!map->isPassble(posX,posY)){
		hero->setAction("The tile is not passible! Re-enter your move!");
		posX = recordX;
		posY = recordY;
	}
}

void Controller::notify(int column, int row, char update){
 	map->notify(column,row,update);
}

bool Controller::play(string filename, int &winState){
	bool done = false;
	bool ifWin = false;
	bool noGenerate = false;
	stayFloor = true;
	if (filename == ""){
		 noGenerate = true;
	}
	// "" means no file provided.
	map = new Map();
	while (!decideRace()){
		cout << "Please enter the correct command!" << endl;
	}
    while(!done){
    	system("clear");
    	if (game->checkWin()){ 
    		// check if hero has reached the fifth floor stair.
    		cout << "You win!" << endl;
    		int score = hero->getGold();
    		if (hero->getType() == "Shade"){
    			score = score * 1.5;
    		}
    		cout << "Your Score is " << score << endl;
    		cout << "Do you want to play again? Press any key to continue, press 'q' to quit!" << endl;
    		ifWin = true;
    		done = true;
    		break;
    	}
    	game->init(this,hero);
    	if (noGenerate){
    		init(*game);
    		// init cell states.
   			game->fillChamber();
   			// connected specific areas of cells.
    		game->generate();
    	}
    	if (!noGenerate){
			init(*game,filename);
			game->fillChamber();
			game->bossRegisterGold();
			// connected a dragon to a neighbour hoard.
    	}
		int posX = hero->getPositionX();
		int posY = hero->getPositionY();
		game->setFloorLevel();
		hero->setAction("Player Character has Spawned");
		stayFloor = true;
		while(stayFloor){
			if (hero->isDied()){
				done = true;
				break;
			}
			system("clear");
			map->printMap();
			game->printInfo();
			string command;
			char command2;
			cin >> command;
			string move1;
			if ((command[0] != 'q' && command[0] != 'a' && command[0] != 'u' 
				&& !ifValid(command) && command[0] != 'r') || command.length() > 3){
				hero->setAction("Wrong Command, please try it again!");	
				continue;
			}
			if (command[0] == 'u' || ifValid(command)){
				if (command[0] == 'u') {
					// if user want to use a potion.
					move1 = command.substr(1,2); // get direction.
 					if (ifValid(move1)){
 						int x = posX;
 						int y = posY;
 						decideDirection(move1,posX,posY);
						if (checkPotion(posX,posY)){ // check if the spot is a potion.
							Potion *Effect = game->findPotion(posX,posY,true);
							Effect->effect(hero);
							string toOut = "PC uses " + Effect->getName()+  "!";
							hero->setAction(toOut);
							game->change(posX,posY,'.');
							posX = x;
							posY = y;
						}
						else{
							posX = x;
							posY = y;
							hero->setAction("No potions there, please try it again!");
						}
					}
					else{
						hero->setAction("Invalid direction! Try again!");
						continue;
					}
				}
				if (ifValid(command)) {
					// if the command is a valid direction, move hero.
					move(posX,posY,command);
				}
				if (hero->isDied()){
					done = true;
					break;
				}
				seePotion();
			}
			if (command[0] == 'a'){
				move1 = command.substr(1,2);
				if (!ifValid(move1)){
					hero->setAction("Invalid direction! Try again!");
					continue;
				}
				bool hasEnemy = fight(move1);
				// simpley attack the enemy at the direction user promoted.
				if (hasEnemy == false){
					hero->setAction("No enemy there, try other directions!");
					continue;
				}
				if (hero->isDied()){
					done = true;
					break;
				}
				game->moveEnemy();//after hero attacked enemies, enemies attack back.
			}
			if (command[0] == 'q' && command.length() == 1){
				cout << "Are you sure you want to quit this game? press 'q' again to quit!" << endl; 
				cin >> command2;
				// double check if user wants to quit the game.
				if (command2 == 'q'){
					done = true;
					break;
				}	
				else{
					continue;
				}
			}
			if (command[0] == 'r' && command.length() == 1){
				cout << "Are you sure you want to restart?, press 'r' again to restart!" << endl;
				cin >> command2;
				if (command2 == 'r'){
					done = true;
					winState = 1; // rdy to restart.
					break;
				}
				else{
					continue;
				}
				
			}
			hero->heroSkill(); // is a valid move is provided, use hero skill.
		}
	}
	if (!ifWin){
		system("clear");
		return false;
	}
	else{
		return true;
	}
}

void Controller::seePotion(){ 
	int x = 0;
	int y = 0;
	bool hasPotion = hero->checkNeighbourPotion(x,y);
	bool ifKnown = false;
	if (hasPotion){
		Potion *find = game->findPotion(x,y,false);
		ifKnown = hero->checkKnown(find);
		// check if the player has already tried this potion.
		if (ifKnown){
			string toOut = " and sees a " + find->getName() + " potion";
			hero->addAction(toOut);
		}
		else{
			hero->addAction(" and sees an unknown potion");
		}
	}

}


Controller::~Controller(){
	delete game;
	delete hero;
	delete map;
}
