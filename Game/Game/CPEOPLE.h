#pragma once
#include "CVEHICLE.h"
#include "CANIMAL.h"
class CPEOPLE {
private:
	int mX, mY;
	char mSymbol = 'Y';
	bool mState;
public:
	CPEOPLE();
	void Up();
	void Left();
	void Right();
	void Down();
	bool isImpact(CVEHICLE*);
	bool isImpact(CANIMAL*);
	bool isFinish();
	bool isDead();
};