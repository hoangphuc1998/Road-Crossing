#pragma once
#include <iostream>
#include <vector>
#include <Windows.h>
#include "CTRUCK.h"
#include "CBIRD.h"
#include "CDINASAUR.h"
#include "CCAR.h"
#include "CPEOPLE.h"
using namespace std;
class CGAME {
private:
	int score =0;
	CPEOPLE *cpe;
	COBJECT **cob;
public:
	void drawBoard();
	CGAME();
	int getScore();
	void drawGame();
	//~CGAME();
	CPEOPLE* getPeople();
	COBJECT* getObject(int);
	void resetGame();
	void exitGame(HANDLE);
	void startGame();
	void loadGame(istream);
	void saveGame(istream);
	void pauseGame(HANDLE);
	void resumeGame(HANDLE);
	void updatePosPeople(char);
	void updatePosObject();
	void increaseScore();
	void updateWhenDie();
};