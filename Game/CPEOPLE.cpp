#include "CPEOPLE.h"

CPEOPLE::CPEOPLE() {
	srand(time(NULL));
	mX = rand() % (width - 1) + 1;
	mY = height - 1;
	mSymbol = 'Y';
	mState = false;
}

CPEOPLE::CPEOPLE(int x, int y) {
	mX = x;
	mY = y;
	mSymbol = 'Y';
	mState = false;
}

void CPEOPLE::Draw() {
	GoToXY(mX, mY);
	cout << mSymbol;
}

bool CPEOPLE::isImpact(COBJECT* c) {
	if (c == NULL) return false;
	return c->isCollide(mX,mY);
}

int CPEOPLE::getY() {
	return mY;
}

int CPEOPLE::getX() {
	return mX;
}

bool CPEOPLE::isFinish() {
	return mY==1;
}

bool CPEOPLE::isDead(){
	return mState;
}

void CPEOPLE::Up() {
	if (mY == 1) {
		return;
	}
	else {
		GoToXY(mX, mY);
		if (checkForLine(mY)) cout << (char)95;
		else cout << " ";
		mY--;
		GoToXY(mX, mY);
		cout << mSymbol;
	}
}

void CPEOPLE::Down() {
	if (mY == height - 1) {
		return;
	}
	else {
		GoToXY(mX, mY);
		if (checkForLine(mY)) cout << (char)95;
		else cout << " ";
		mY++;
		GoToXY(mX, mY);
		cout << mSymbol;
	}
}

void CPEOPLE::Right() {
	GoToXY(mX, mY);
	if (checkForLine(mY)) cout << (char)95;
	else cout << " ";
	mX++;
	mX = mX % (width - 1) + 1;
	GoToXY(mX, mY);
	cout << mSymbol;
}

void CPEOPLE::Left() {
	GoToXY(mX, mY);
	if (checkForLine(mY)) cout << (char)95;
	else cout << " ";
	mX--;
	if (mX == 0) mX = width - 1;
	GoToXY(mX, mY);
	cout << mSymbol;
}

void CPEOPLE::updateWhenFinish() {
	mX = rand() % (width - 1) + 1;
	mY = height-1;
	Draw();
}

void CPEOPLE::collide() {
	mState = true;
}