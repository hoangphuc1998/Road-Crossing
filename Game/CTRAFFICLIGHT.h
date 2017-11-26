#pragma once
#include <iostream>
#include "Function.h"
#include <Windows.h>
using namespace std;
class CTRAFFICLIGHT {
private:
	bool mIsRed;
	int mTimeToChange;
	int mClock;
	int mX, mY;
public:
	CTRAFFICLIGHT(int,int,int);
	void drawWhenStart();
	void updateTime();
	bool isRed();
	void save(FILE* os);
	void load(FILE* is);
};