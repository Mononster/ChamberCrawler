#include "vampire.h"

using namespace std;

Vampire::Vampire(int atk,int def,int hp, char name)
:Hero(atk,def,hp,hp,name,0){
	type = "Vampire";
}

