#pragma once
#include "Function.h"
class CVEHICLE {
private:
	int mX;
	int mY;
	bool mGoLeft;
	char mSymbol;
	int mLength = width / 2;;
public:
	CVEHICLE(int,char);
	void draw();
	void Move(int,int);
};