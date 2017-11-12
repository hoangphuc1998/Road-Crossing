#pragma once
#include "Function.h"
class COBJECT {
private:
	int mX, mY;
	bool mGoLeft;
	char mSymbol;
	int mLength=width/3;
public:
	COBJECT(int, char);
	void Draw();
	void Move();
	bool isCollide(int);
	virtual void Tell() { return; };
	virtual ~COBJECT() {};
};