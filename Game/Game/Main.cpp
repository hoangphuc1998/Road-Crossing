#include <thread>
#include <iostream>
#include <conio.h>
#include "Function.h"
#include "CGAME.h"
using namespace std;
bool IS_RUNNING = true;
char MOVING;
CGAME cg;
void exitGame(thread *t) {
	system("cls");
	IS_RUNNING = false;
	t->join();
}

void ThreadFunc() {
	while (IS_RUNNING) {
		if (!cg.getPeople().isDead()) {
			cg.updatePosPeople(MOVING);
		}
		MOVING = ' ';
		cg.updatePosVehicle();
		cg.updatePosAnimal();
		cg.drawGame();
		if (cg.getPeople().isImpact(cg.getVehicle())
			|| cg.getPeople().isImpact(cg.getAnimal())) {
			//Xu li dung xe hay thu
		}
		if (cg.getPeople().isFinish()) {
			//Xu li khi ve dich
		}
		Sleep(100+cg.getScore());
	}
}

void main() {
	cg = CGAME();
	int temp;
	FixConsoleWindow();
	cg.startGame();
	thread t1(ThreadFunc);
	while (1) {
		temp = toupper(_getch());
		//...
		if (!cg.getPeople().isDead()) {
			if (temp == 27) {
				exitGame(&t1);
				return;
			}
			else if (temp == 'P') {
				cg.pauseGame(t1.native_handle());
			}
			else {
				cg.resumeGame((HANDLE)t1.native_handle());
				MOVING = temp;
			}
		}
		else {
			if (temp == 'Y') cg.startGame();
			else {
				cg.exitGame(t1.native_handle());
				return;
			}
		}
	}
}