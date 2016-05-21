#include "tresure.h"

Tresure::Tresure(int value,Cell* update,bool ifgetprotectd,std::string name) :
 Item(name,update),value(value),ifgetProtected(ifgetprotectd){}

bool Tresure::getProtected() const{
	return ifgetProtected;
}

int Tresure::getValue() const{
	return value;
}

void Tresure::setProtected(bool toset){
	ifgetProtected = toset;
}

 Tresure::~Tresure(){}
