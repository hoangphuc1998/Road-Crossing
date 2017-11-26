#include "CTRAFFICLIGHT.h"

CTRAFFICLIGHT::CTRAFFICLIGHT(int time,int x,int y) {
	
	mIsRed = false;
	mTimeToChange = time;
	mClock = 0;
	mX = x;
	mY = y;
}

void CTRAFFICLIGHT::drawWhenStart() {
	CONSOLE_SCREEN_BUFFER_INFO info;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsole, &info);
	if (mIsRed) {
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
	}
	else SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
	GoToXY(mX, mY);
	cout << (char)219;
	GoToXY(mX + 3, mY);
	cout << mTimeToChange-mClock;
	SetConsoleTextAttribute(hConsole, info.wAttributes);
}
void CTRAFFICLIGHT::updateTime() {
	mClock++;
	CONSOLE_SCREEN_BUFFER_INFO info;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsole, &info);
	if (mIsRed) {
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
	}
	else SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
	GoToXY(mX + 3, mY);
	if (mTimeToChange - mClock < 10)cout << "0";
	cout << mTimeToChange - mClock;
	if (mClock == mTimeToChange) {
		if (mIsRed) {
			SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
			GoToXY(mX, mY);
			cout << (char)219;
			mIsRed = false;
		}
		else {
			mIsRed = true;
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
			GoToXY(mX, mY);
			cout << (char)219;
		}
		mClock = 0;
		GoToXY(mX + 3, mY);
		cout << mTimeToChange;
	}
	SetConsoleTextAttribute(hConsole, info.wAttributes);
}

bool CTRAFFICLIGHT::isRed() {
	return mIsRed;
}

void CTRAFFICLIGHT::save(FILE* os) {
	fprintf(os, "%d %d %d %d %d ", mIsRed, mTimeToChange, mClock, mX, mY);
}

void CTRAFFICLIGHT::load(FILE* is) {
	fscanf(is, "%d %d %d %d %d ", &mIsRed, &mTimeToChange, &mClock, &mX, &mY);
}