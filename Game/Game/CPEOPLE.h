#pragma once
#include "CVEHICLE.h"
#include "CANIMAL.h"
class CPEOPLE {
private:
	int mX, mY;
	char mSymbol = 'Y';
	bool mState; //is People dead
public:
	CPEOPLE();
	int getY();
	void Draw();
	void Up();
	void Left();
	void Right();
	void Down();
	bool isImpact(COBJECT*);
	bool isFinish();
	bool isDead();
	void updateWhenFinish();
	void collide();
};