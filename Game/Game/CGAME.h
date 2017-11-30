#pragma once
#include <thread>
#include <conio.h>
#include <iostream>
#include <vector>
#include <Windows.h>
#include "CTRUCK.h"
#include "CBIRD.h"
#include "CDINASAUR.h"
#include "CCAR.h"
#include "CPEOPLE.h"
#include "CTRAFFICLIGHT.h"
using namespace std;
class CGAME {
private:
	int score =0;
	CPEOPLE *cpe;
	vector<COBJECT*> cob;
	CTRAFFICLIGHT *mLight1, *mLight2;
public:
	void updateTrafficLight();
	void drawBoard();
	CGAME();
	void drawGame();
	CPEOPLE* getPeople();
	bool isPeopleCrash();
	void resetGame();
	void exitGame(HANDLE);
	void startGame();
	bool loadGame(char*);
	bool saveGame(char*);
	void pauseGame(HANDLE,HANDLE);
	void resumeGame(HANDLE,HANDLE);
	void updatePosPeople(char);
	void updatePosObject();
	void increaseScore();
	void updateWhenDie();
	void DrawMenuWhenStart();
	void DrawGameName();
};