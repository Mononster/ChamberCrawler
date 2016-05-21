#include "cell.h"
#include "game.h"

using namespace std;

Cell::Cell() : numNeighbours(0){}


void Cell::addNeighbour(Cell *neighbour){
	this->neighbours[numNeighbours] = neighbour;
	numNeighbours++;
}

void Cell::lookUp(){
	// recursively look up the neighbours of the cell to find the state with
	// state '.' and add it to the chamber.
	this->visited = true;
	game->fillChamber(this);
	for (int i = 0; i < MAXNEIGHBOURS;i++){
		if (neighbours[i]->state == '.' && neighbours[i]->visited == false){
			neighbours[i]->lookUp();
		}
		neighbours[i]->visited = true;
	}
}

Cell* Cell::getNeighbours(int index) const{
	return neighbours[index];
}
int Cell::getPositionX() const{
	return positionX;
}
int Cell::getPositionY() const{
	return positionY;
}
char Cell::getPrev() const{
	return prevState;
}
char Cell::getState() const{
	return state;
}
bool Cell::getVisited() const{
	return visited;
}
void Cell::notifyGame() const{
	// notifyGame that i have changed the state.
	game->notify(positionY,positionX,state);
}
void Cell::setState(const char& change){
	state = change;
} 
void Cell::setPrev(const char& change){
	prevState = change;
}

void Cell::setCoords(const int column, const int row){
	this->positionY= row;
	this->positionX = column;
}
void Cell::setGame(Game *game){
	//register game.
	this->game = game;
}

void Cell::setVisit(bool b){
	visited = b;
}

Cell::~Cell(){}

