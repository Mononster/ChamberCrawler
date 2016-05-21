#ifndef Merchant_H
#define Merchant_H

#include "enemy.h"

class Merchant : public Enemy
{
public:
	Merchant(Cell *toRegister,int atk = 20,int def = 30,int hp = 100, char name = MERCHANT);
	~Merchant(){};

	/* data */
};

#endif
