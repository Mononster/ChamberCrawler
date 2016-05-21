#include "tresure.h"

Tresure::Tresure(int value,Cell* update,bool ifgetprotectd,std::string name) :
 Item(name,update),value(value),ifgetProtected(ifgetprotectd){}

 Tresure::~Tresure(){}

 int Tresure::getValue(){
 	return value;
 }

 void Tresure::setProtected(bool toset){
 	ifgetProtected = toset;
 }
bool Tresure::getProtected(){
	return ifgetProtected;
}

