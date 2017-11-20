#include "COBJECT.h"
COBJECT::COBJECT(int y, char s) {
	mSymbol = s;
	mGoLeft = rand() % 2;
	mY = y;
	mX = rand() % (width - 1) + 1;
}

void COBJECT::Draw() {
	for (int i = mX; i < mX + mLength; i++) {
		if (i >= width)
			GoToXY(i%width + 1, mY);
		else GoToXY(i, mY);
		cout << mSymbol;
	}
}

void COBJECT::Move() {
	if (mGoLeft) {
		int i = mX + mLength - 1;
		if (i >= width)
			GoToXY(i % width + 1, mY);
		else GoToXY(i, mY);
		cout << " ";
		if (mX == 1) {
			mX = width - 1;
		}
		else mX--;
		GoToXY(mX, mY);
		cout << mSymbol;
	}
	else {
		GoToXY(mX, mY);
		cout << " ";
		if (mX == width - 1) mX = 1;
		else mX++;
		int i = mX + mLength - 1;
		if (i >= width)
			GoToXY(i % width + 1, mY);
		else GoToXY(i, mY);
		cout << mSymbol;
	}	
}

bool COBJECT::isCollide(int x) {
	int i = mX + mLength - 1;
	if (i >= width) {
		return (x >= mX && x <= width - 1)
			|| (x >= 1 && x <= (i%width) + 1);
	}
	else {
		return x >= mX && x <= i;
	}
}