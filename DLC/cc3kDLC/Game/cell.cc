#include "cell.h"
#include "game.h"

using namespace std;

Cell::Cell() : numNeighbours(0){}
Cell::~Cell(){}
char Cell::getState() const{
	return state;
}         //getter for private state
char Cell::getPrev() const{
	return prevState;
}
bool Cell::getVisited() const{
	return visited;
}
int Cell::getPositionX() const{
	return PositionX;
}
int Cell::getPositionY() const{
	return PositionY;
}
void Cell::setChamberIndex(int chamberIndex){
	this->chamberIndex = chamberIndex;
}
int Cell::getChamberIndex(){
	return chamberIndex;
}
Cell* Cell::getNeighbours(int index){
	return neighbours[index];
}
void Cell::setState(const char& change){
	state = change;
}      //setter for private state
void Cell::setPrev(const char& change){
	prevState = change;
}
void Cell::notifyGame() const{
	game->notify(PositionY,PositionX,state,chamberIndex);
}

void Cell::setCoords(const int column, const int row){
	this->PositionY= row;
	this->PositionX = column;
}
void Cell::setGame(Game *game){
	this->game = game;
}

void Cell::setVisit(bool b){
	visited = b;
}

void Cell::addNeighbour(Cell *neighbour){

	this->neighbours[numNeighbours] = neighbour;
	//cout << neighbours[numNeighbours]->state << endl;
	numNeighbours++;
	//cout << this->PositionX << " " << this->PositionY << " "<< numNeighbours << endl;
}

void Cell::lookUp(int chamberNumber){
	//printw("!");
	this->visited = true;
	game->fillChamber(this);
	setChamberIndex(chamberNumber);
	for (int i = 0; i < MAXNEIGHBOURS;i++){
		if (neighbours[i]->state != '.'){
			neighbours[i]->visited = true;
			neighbours[i]->setChamberIndex(chamberNumber);
			game->fillChamber(neighbours[i]);
		}
		if (neighbours[i]->state == '.' && neighbours[i]->visited == false){
			neighbours[i]->lookUp(chamberNumber);
		}
	}

	
}