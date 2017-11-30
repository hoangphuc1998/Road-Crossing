#include "COBJECT.h"
COBJECT::COBJECT(int x,int y) {
	mX = x;
	mY = y;
}

int COBJECT::getNewX() {
	int k = mX + 8;
	if (k >= width)k = k%width + 1;
	return k;
}

int COBJECT::getX() {
	return mX;
}

int COBJECT::getY() {
	return mY;
}