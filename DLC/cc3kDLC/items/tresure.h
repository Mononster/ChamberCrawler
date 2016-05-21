#ifndef TRESURE_H
#define TRESURE_H

#include "item.h"

class Tresure : public Item
{
	int value;
	bool ifgetProtected;
public:
	int getValue();
	Tresure(int value,Cell* update,bool ifgetProtected = false,std::string name = "gold");
	~Tresure();
	void setProtected(bool toset);
	bool getProtected();
	/* data */
};



#endif
