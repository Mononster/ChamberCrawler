#include "shade.h"

using namespace std;

Shade::Shade(int atk,int def,int hp, char name) 
			:Hero(atk,def,hp,hp,name,0){
	type = "Shade";
}

