#ifndef Merchant_H
#define Merchant_H

#include "enemy.h"

class Merchant : public Enemy
{
public:
	Merchant(Cell *toRegister,int atk = 70,int def = 5,int hp = 30, char name = MERCHANT);
	~Merchant(){};
};

#endif

