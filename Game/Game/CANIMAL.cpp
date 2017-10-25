#include "CANIMAL.h"
void CANIMAL::draw() {
	for (int i = mX; i <= mX + mLength; i++) {
		if (i>=width)
			GoToXY(i%width+1, mY);
		else GoToXY(i, mY);
		cout << mSymbol;
	}
}

CANIMAL::CANIMAL(int y,char s) {
	srand(time(NULL));
	mSymbol = s;
	mGoLeft = rand() % 2;
	mY = y;
	mX = rand() % (width - 1) + 1;
}

