#include "CVEHICLE.h"
void CVEHICLE::draw() {
	for (int i = mX; i <= mX + mLength; i++) {
		if (i >= width)
			GoToXY(i%width + 1, mY);
		else GoToXY(i, mY);
		cout << mSymbol;
	}
}

CVEHICLE::CVEHICLE(int y,char s) {
	srand(time(NULL));
	mSymbol = s;
	mGoLeft = rand() % 2;
	mY = y;
	mX = rand() % (width - 1) + 1;
}

