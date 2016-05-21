#include "goblin.h"

using namespace std;

Goblin::Goblin(int atk,int def,int hp, char name) 
:Hero(atk,def,hp,hp,name,0){
		type = "Goblin";
}

