#include "CBIRD.h"
CBIRD::CBIRD(int x,int y) :CANIMAL(x,y) {};
void CBIRD::Draw() {
	GoToXY(mX, mY-1);
	cout << (char)219;
	if (mX + 1 < width) {
		GoToXY(mX + 1, mY);
		cout << (char)219;
	}
	else {
		int k = (mX + 1) % width + 1;
		GoToXY(k, mY);
		cout << (char)219;
	}
	if (mX + 2 < width) {
		GoToXY(mX + 2, mY - 1);
		cout << (char)219;
	}
	else {
		int k = (mX + 2) % width + 1;
		GoToXY(k, mY - 1);
		cout << (char)219;
	}
}

void CBIRD::Move() {
	GoToXY(mX, mY - 1);
	cout << " ";
	if (mX + 1 < width) {
		GoToXY(mX + 1, mY);
		cout << " ";
	}
	else {
		int k = (mX + 1) % width + 1;
		GoToXY(k, mY);
		cout << " ";
	}
	if (mX + 2 < width) {
		GoToXY(mX + 2, mY - 1);
		cout << " ";
	}
	else {
		int k = (mX + 2) % width + 1;
		GoToXY(k, mY - 1);
		cout << " ";
	}
	mX--;
	if (mX == 0) mX = width - 1;
	Draw();
}

bool CBIRD::isCollide(int x, int y) {
	if (x == mX && y == mY - 1) return true;
	int k=mX+1;
	if (mX + 1 >= width) {
		k = (mX + 1) % width + 1;
	}
	if (x == k && y == mY) return true;
	k = mX + 2;
	if (mX + 2 >= width) {
		k = (mX + 2) % width + 1;
	}
	if (x == k && y == mY - 1)return true;
	return false;
}