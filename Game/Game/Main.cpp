#include <thread>
#include <iostream>
#include <conio.h>
#include "CGAME.h"
using namespace std;

bool IS_RUNNING = true;
char MOVING;
CGAME cg = CGAME();
void exitGame(thread *t) {
	system("cls");
	IS_RUNNING = false;
	t->join();
}

void ThreadFunc() {
	while (IS_RUNNING) {
		if (!cg.getPeople()->isDead()) {
			cg.updatePosPeople(MOVING);
		}
		MOVING = ' ';
		cg.updatePosObject();
		if (cg.getPeople()->isImpact(cg.getObject(cg.getPeople()->getY()))) {
			cg.getPeople()->collide();
			IS_RUNNING = false;
			cg.updateWhenDie();
		}
		if (cg.getPeople()->isFinish()) {
			cg.increaseScore();
		}
		Sleep(100+cg.getScore());
	}
}

void main() {
	int temp;
	FixConsoleWindow();
	cg.startGame();
	thread t1(ThreadFunc);
	while (1) {
		temp = toupper(_getch());
		//...
		if (!cg.getPeople()->isDead()) {
			if (temp == 27) {
				exitGame(&t1);
				t1.join();
				return;
			}
			/*else if (temp == 'P') {
				cg.pauseGame(t1.native_handle());
			}*/
			else {
				cg.resumeGame((HANDLE)t1.native_handle());
				MOVING = temp;
			}
		}
		else {
			if (temp == 'Y') {
				cg.resetGame();
				cg.startGame();
				IS_RUNNING = true;
			}
			else {
				cg.exitGame(t1.native_handle());
				t1.join();
				return;
			}
		}
	}
}