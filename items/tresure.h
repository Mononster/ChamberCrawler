#ifndef TRESURE_H
#define TRESURE_H

#include "item.h"

class Tresure : public Item
{
	int value;
	bool ifgetProtected;
public:
	Tresure(int value,Cell* update,bool ifgetProtected = false,std::string name = "gold");
	bool getProtected() const;
	// if the tresure is a dragon hoard(protected by a dragon).
	int getValue() const;
	void setProtected(bool toset);
	~Tresure();
};



#endif
