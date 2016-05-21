#include "drow.h"

using namespace std;

Drow::Drow(int atk,int def,int hp, char name) 
:Hero(atk,def,hp,hp,name,0){
	type = "Drow";
}

