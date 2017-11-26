#pragma once
#include "CVEHICLE.h"
#include "CANIMAL.h"
class CPEOPLE {
private:
	int mX, mY;
	char mSymbol;
	bool mState; //is People dead
public:
	CPEOPLE();
	CPEOPLE(int, int);
	int getX();
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