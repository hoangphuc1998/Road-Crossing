#include "CTRUCK.h"

CTRUCK::CTRUCK(int x,int y) :CVEHICLE(x,y) {};

void CTRUCK::Draw() {
	GoToXY(mX, mY);
	cout << (char)219;
	if (mX + 1 < width) {
		GoToXY(mX + 1, mY);
		cout << (char)219;
		GoToXY(mX + 1, mY - 1);
		cout << (char)219;
	}
	else {
		int k = (mX + 1) % width + 1;
		GoToXY(k, mY);
		cout << (char)219;
		GoToXY(k, mY - 1);
		cout << (char)219;
	}
	if (mX + 2 < width) {
		GoToXY(mX + 2, mY);
		cout << (char)219;
		GoToXY(mX + 2, mY - 1);
		cout << (char)219;
	}
	else {
		int k = (mX + 2) % width + 1;
		GoToXY(k, mY);
		cout << (char)219;
		GoToXY(k, mY - 1);
		cout << (char)219;
	}
}

void CTRUCK::Move() {
	if (mX + 2 < width) {
		GoToXY(mX + 2, mY);
		cout << (char)95;
		GoToXY(mX + 2, mY - 1);
		cout << " ";
	}
	else {
		int k = (mX + 2) % width + 1;
		GoToXY(k, mY);
		cout << (char)95;
		GoToXY(k, mY - 1);
		cout << " ";
	}
	mX--;
	if (mX == 0)mX = width - 1;
	GoToXY(mX, mY);
	cout << (char)219;
	if (mX + 1 < width) {
		GoToXY(mX + 1, mY - 1);
		cout << (char)219;
	}
	else {
		int k = (mX + 1) % width + 1;
		GoToXY(k, mY - 1);
		cout << (char)219;
	}
}

bool CTRUCK::isCollide(int x, int y) {
	if (x == mX && y == mY) return true;
	int k = mX + 1;
	if (mX + 1 >= width) {
		k = (mX + 1) % width + 1;
	}
	if (x == k && (y == mY || y == mY - 1)) return true;
	k = mX + 2;
	if (mX + 2 >= width) {
		k = (mX + 2) % width + 1;
	}
	if (x == k && (y == mY || y == mY - 1))return true;
	return false;
}