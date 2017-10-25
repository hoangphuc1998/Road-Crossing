#pragma once
#include "Function.h"
class CANIMAL {
private:
	int mX, mY;
	bool mGoLeft;
	char mSymbol;
	int mLength = width/2;
public:
	CANIMAL(int,char);
	void Move();
	virtual void Tell();
	void draw();
};