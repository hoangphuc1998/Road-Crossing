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
	vector<CTRUCK>ctr;
	vector<CCAR> cca;
	vector<CDINASAUR> cdi;
	vector<CBIRD> cbi;
	CPEOPLE cpe();
	CANIMAL **rowAnimal;
	CVEHICLE **rowVehicle;
public:
	void drawBoard();
	CGAME();
	int getScore();
	void drawGame();
	~CGAME();
	CPEOPLE getPeople();
	CANIMAL* getAnimal(int);
	CVEHICLE* getVehicle(int);
	void resetGame();
	void exitGame(HANDLE);
	void startGame();
	void loadGame(istream);
	void saveGame(istream);
	void pauseGame(HANDLE);
	void resumeGame(HANDLE);
	void updatePosPeople(char);
	void updatePosVehicle();
	void updatePosAnimal();
};