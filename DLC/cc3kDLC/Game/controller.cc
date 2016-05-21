#include "controller.h"

using namespace std;

Controller::Controller(){
  game = new Game();
  map = NULL;
  hero = NULL;
  fileRow = 0;
}

bool ifValid(string direction){
	if((direction == "no") || direction == "ea" || direction == "we" || direction =="so"
		||direction == "nw" || direction == "sw" || direction == "ne" || direction == "se"){
		return true;
	}
	return false;
}

void Controller::notify(int column, int row, char update){
  map->notify(column,row,update);
}

void Controller::init(Game &g, string filename = "defaultLevel.txt"){
    ifstream file(filename.c_str());
	*game = g;
	string input;
	char record;
	int length;
	int row = 0;
	int beginFile = 1;
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
		//printw( row );
	}
	if (filename != "defaultLevel.txt"){
		fileRow = MAP_HEIGHT * (game->getFloorLevel()+1) +1;
	}
	//printw( "fileRow == " << fileRow );
}
bool Controller::checkStair(int x, int y){
	if (map->getValue(x,y) == STAIR){
		return true;
	}
	return false;
}
bool Controller::checkGold(int x, int y){
	if (map->getValue(x,y) == GOLD){
		return true;
	}
	return false;
}
bool Controller::checkPotion(int x, int y){
	if (map->getValue(x,y) == POTION){
		return true;
	}
	return false;
}

bool Controller::checkMerchant(int x, int y){
	if (map->getValue(x,y) == MERCHANT){
		return true;
	}
	return false;
}

bool Controller::checkEnemy(int x, int y){
	if (map->getValue(x,y) == HUMAN || 
		map->getValue(x,y) == DWARF || 
		map->getValue(x,y) == HALFLING ||
		map->getValue(x,y) == ORC ||
		map->getValue(x,y) == ELF ||
		map->getValue(x,y) == MERCHANT ||
		map->getValue(x,y) == DRAGON){
		return true;
	}
	return false;
}
void Controller::decideDirection(string direction,int &x, int &y){
	int recordX = x;
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

void Controller::showPassWay(Cell *cell){
	for (int i = 0; i<MAXNEIGHBOURS;i++){
		Cell *neighbour = cell->getNeighbours(i);
		if (neighbour->getState() == '#'){
			game->notify(neighbour->getPositionX(),neighbour->getPositionY(),'#',-2);
		}
	}
}
void Controller::showDoor(Cell *cell){
	for (int i = 0; i<MAXNEIGHBOURS;i++){
		Cell *neighbour = cell->getNeighbours(i);
		if (neighbour->getState() == '+'){
			game->notify(neighbour->getPositionX(),neighbour->getPositionY(),'+',-3);
		}
	}
}
void Controller::move(int &posX, int &posY,string move){
	int recordX = posX;
	int recordY = posY;
	decideDirection(move,posX,posY);
	Cell currCell = game->getCell(posX,posY);
	if (map->isPassble(posX, posY)){
		char lastPos = game->getCell(recordX,recordY).getPrev();
		char pos = HERO;

		if (map->getValue(posX,posY) == '+' || map->getValue(posX,posY) == '.'){
			int chamberIndex = game->searchChamber(posX,posY);
			game->notify(chamberIndex);
			showPassWay(&currCell);
		}
		if (map->getValue(posX,posY) == '#'){
			showPassWay(&currCell);
			showDoor(&currCell);
			//game->notify(posX,posY,HERO,-2);
		}
		if (checkStair(posX, posY)){
			stayFloor = false;
			return;
		}
		if (checkGold(posX,posY)){
			int value = game->findValue(posX,posY);
			bool protectd = game->findTresure(posX,posY)->getProtected();
			if (!protectd){
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
			}
		}
		if (checkPotion(posX,posY)){
			Potion *Effect = game->findPotion(posX,posY,true);
			bool ifKnown = hero->checkKnown(Effect);
			if (ifKnown){
				string toOut = "PC picks " + Effect->getName()+  " up !";
				hero->setAction(toOut);
			}
			else{
				string toOut = "PC picks up an unknown effect potion!";
				hero->setAction(toOut);
			}
		}

		hero->setPositionX(posX);
		hero->setPositionY(posY);
		//printw( recordX << " "<< recordY <<" " << lastPos );	
		//printw( posX << " "<< posY <<" " << HERO );	
		game->change(recordX,recordY,lastPos);
		game->change(posX,posY,pos);
		game->moveEnemy();	
		return;
	}
	if (!map->isPassble(posX,posY)){
		if (checkEnemy(posX,posY)){
			fight(move);
			game->moveEnemy();
			posX = recordX;
			posY = recordY;
		}
		else{
			hero->setAction("The tile is not passible! Re-enter your move!");
			posX = recordX;
			posY = recordY;
		}
	}
}
void Controller::fight(string direction){
	//printw( direction );
	bool hasEnemy = false;
	int x = 0;
	int y = 0;
	decideDirection(direction,x,y);
	//printw( x <<" " << y );
	hasEnemy = hero->checkNeighbourEnemy(x,y);
	if (hasEnemy){
		bool ifDied = game->heroAttack(x,y); // if enemy is died.
		if (ifDied){
			//system("clear");
			map->printMap();
			game->printInfo();
		}
	}
	else {
		hero->setAction("No enemy there!");
	}
}
void Controller::seePotion(){
	int x = 0;
	int y = 0;
	bool hasPotion = hero->checkNeighbourPotion(x,y); 
	// check if there is potion beside hero and mutate x and y to the position.
	bool ifKnown = false;
	if (hasPotion){
		Potion *find = game->findPotion(x,y,false);
		ifKnown = hero->checkKnown(find);
		if (ifKnown){
			string toOut = " and sees a " + find->getName() + " potion";
			hero->addAction(toOut);
		}
		else{
			hero->addAction(" and sees an unknown potion");
		}
	}

}
bool Controller::decideRace(){
	int race;
	race = getch();

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

bool Controller::checkAtkDirection(string move){
	if (move == "nw" || move == "ne" || move == "sw" || move == "se"){
		return true;
	}
	return false;
}
string Controller::convertMove(int move){
	switch(move){
		case KEY_UP: 
		return "no";
		case KEY_DOWN:
		return "so";
		case KEY_LEFT:
		return "we";
		case KEY_RIGHT:
		return "ea";
		case 'q':
		return "q";
		case 'r':
		return "r";
		case 'i':
		return "i";
		case 'd':
		return "d";
		case 'b':
		return "b";
		case 'j':
		return "nw";
		case 'k':
		return "ne";
		case 'l':
		return "sw";
		case ';':
		return "se";
	}
	return "";
}
bool Controller::play(string filename, int &winState){
	srand(time(NULL));
	bool done = false;
	bool ifWin = false;
	bool noGenerate = false;
	stayFloor = true;
	if (filename == ""){
		noGenerate = true;
	}
	map = new Map();

	while (!decideRace()){
		printw( "Please enter the correct command!" );
	}
	nodelay(stdscr,true);
    while(!done){
    	//system("clear");
    	map->clearMap();
    	if (game->checkWin()){
    		printw( "You win!" );
    		ifWin = true;
    		done = true;
    		break;
    	}
    	game->init(this,hero);
    	if (noGenerate){
    		init(*game);
   	 	game->fillChamber();
    		game->generate(1);
    	}
    	if (!noGenerate){
			init(*game,filename);
			game->fillChamber();
			game->generate(0);
			//game->bossRegisterGold();
    	}
		int posX = hero->getPositionX();
		int posY = hero->getPositionY();
		game->setFloorLevel();
		hero->setAction("Player Character has Spawned");
		//printw( "floor == "<< game->getFloorLevel() );

		map->printMap();
		game->printInfo();
		stayFloor = true;
		while(stayFloor){
			int  command;
			int command2;
			command = getch();
			string move1;
			move1 = convertMove(command);
			//printw( command );
			if (ifValid(move1)){
				move(posX,posY,move1);
				if (hero->isDied()){
					done = true;
					break;
				}
				seePotion();
				if (stayFloor){
					map->printMap();
					game->printInfo();
				}
			}
			if (move1 == "q"){
				nodelay(stdscr,false);
				printw( "Are you sure you want to quit this game? press 'q' again to quit!" ); 
				command2 = getch();
				if (command2 == 'q'){
					done = true;
					break;
				}	
			}
			if (move1 == "b"){
				nodelay(stdscr,false);
				Cell heroCell = game->getCell(posX,posY);
				bool ifhasMerchant = false;
				for (int i = 0; i< MAXNEIGHBOURS; i++){
					if (heroCell.getNeighbours(i)->getState() == MERCHANT){
						ifhasMerchant = true;
						break;
					}
				}
				if (ifhasMerchant){
					buy();
					bool doneBuy = false;
					while(!doneBuy){
						command2 = getch();
						game->buyFromMerchant(command2);
						if (command2 == 'q'){
  							doneBuy = true;
  							break;
  						}
					}
					hero->setAction("Hero shoped!");
				}
				if (!ifhasMerchant){
					hero->setAction("Sorry, there isn't any merchant beside you!");
				}
				map->printMap();
				game->printInfo();
				nodelay(stdscr,true);
			}
			if (move1 == "r"){
				nodelay(stdscr,false);
				printw( "Are you sure you want to restart?, press 'r' again to restart!" );
				command2 = getch();
				if (command2 == 'r'){
					done = true;
					winState = 1; // rdy to restart.
					break;
				}
				map->printMap();
				game->printInfo();
				nodelay(stdscr,true);
			}
			if (move1 == "i"){
				nodelay(stdscr,false);
				bool doneDrink = false;
				game->getInventory()->print();
				printw("Press 'd' to drink!\n");
				while (!doneDrink){
					command2 = getch();
					if (command2 == 'd'){
						printw("Choose which one you one to drink, enter the corresponding number for potions.\n");
						command2 = getch();
						//printw("command2 == %d\n",command2-'0');
						game->getInventory()->usePotion(command2-'0');
						printw("Press 'q' to quit, press 'd' to drink again\n");
					}else if (command2 == 'q'){
						doneDrink = true;
						break;
					}else{
						printw("Wrong command, please try it again!");
					}
				}
				map->printMap();
				game->printInfo();
				nodelay(stdscr,true);
			}
			if (!ifValid(move1) && move1 != "q" && move1 != "b" && move1 != "r"
				&& move1 != "i"){
			//	hero->setAction("Wrong Command, please try it again!");
				continue;
			}	
			hero->heroSkill();
		}
	}
	if (!ifWin){
		//system("clear");
		return false;
	}
	else{
		return true;
	}
}
void Controller::buy(){
	clear();
	printw("Hello! This is the merchant shop, and here is the list of options you can choose to improve your power!\n");
 	printw("Z. Buy 100 Hp (25 golds)\n");
 	printw("X. Buy 8 Def (25 golds)\n");
 	printw("C. Buy 8 Atk (25 golds)\n");
 	printw("Choose which one you want!\n");
 	printw("Press 'q' to quit shop\n");
}
Controller::~Controller(){
	delete map;
	delete game;
	delete hero;
}

