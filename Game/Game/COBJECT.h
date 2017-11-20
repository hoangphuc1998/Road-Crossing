#pragma once
#include "Function.h"
class COBJECT {
protected:
	int mX, mY;
public:
	int getNewX();
	COBJECT(int,int);
	virtual void Draw() = 0;
	virtual void Move() = 0;
	virtual bool isCollide(int,int) = 0;
};