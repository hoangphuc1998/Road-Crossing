#include "CGAME.h"
bool IS_RUNNING = true;
char MOVING;
CGAME cg = CGAME();

void SoundThread() {
	while (IS_RUNNING) {
		if (!cg.getPeople()->isDead()) {
			int y = cg.getPeople()->getY();
			if(y>=2 && y<=5)
				PlaySound(TEXT("dinosaur.wav"), NULL, SND_FILENAME);
			if (y >= 6 && y <= 9)
				PlaySound(TEXT("bird.wav"), NULL, SND_FILENAME);
		}
	}
}

void ThreadFunc() {
	while (IS_RUNNING) {
		if (!cg.getPeople()->isDead()) {
			cg.updateTrafficLight();
			cg.updatePosObject();
			cg.updatePosPeople(MOVING);
			MOVING = ' ';
			if (cg.isPeopleCrash()) {
				cg.getPeople()->collide();
				cg.updateWhenDie();
			}
			if (cg.getPeople()->isFinish()) {
				cg.increaseScore();
			}
			Sleep(100);
		}
	}
}

void main() {
	int temp;
	FixConsoleWindow();
	//Xu li ve menu khi bat dau
	cg.DrawMenuWhenStart();
	temp = toupper(_getch());
	int choose = 1;
	while (temp != 13) {
		if (temp == 'W') {
			if (choose == 2) {
				GoToXY(width / 2 - 3, height / 2);
				cout << "->";
				GoToXY(width / 2 - 3, height / 2+1);
				cout << "  ";
				choose = 1;
			}
			else if (choose == 3) {
				GoToXY(width / 2 - 3, height / 2+1);
				cout << "->";
				GoToXY(width / 2 - 3, height / 2 + 2);
				cout << "  ";
				choose = 2;
			}
		}
		if (temp == 'S') {
			if (choose == 1) {
				GoToXY(width / 2 - 3, height / 2+1);
				cout << "->";
				GoToXY(width / 2 - 3, height / 2);
				cout << "  ";
				choose = 2;
			}
			else if (choose == 2) {
				GoToXY(width / 2 - 3, height / 2 + 2);
				cout << "->";
				GoToXY(width / 2 - 3, height / 2 + 1);
				cout << "  ";
				choose = 3;
			}
		}
		temp = toupper(_getch());
	}
	if (choose == 2) {
		system("cls");
		char s[100];
		GoToXY(width / 2, height / 2);
		cout << "Enter file name: ";
		fgets(s, 101, stdin);
		s[strlen(s) - 1] = '\0';
		system("cls");
		bool kt = cg.loadGame(s);
		if (kt) {
			GoToXY(width / 2, height / 2);
			cout << "Load successful";
			GoToXY(width / 2, height / 2 + 1);
			system("pause");
		}
		else {
			GoToXY(width / 2, height / 2);
			cout << "Load failed";
			GoToXY(width / 2, height / 2 + 1);
			system("pause");
		}
	}
	cg.startGame();
	thread t1(ThreadFunc);
	thread t2(SoundThread);
	while (1) {
		temp = toupper(_getch());
		if (!cg.getPeople()->isDead()) {
			if (temp == 27) {
				cg.exitGame(t1.native_handle());
				t1.join();
				cg.exitGame(t2.native_handle());
				t2.join();
				return;
			}
			else if (temp == 'P') {
				cg.pauseGame(t1.native_handle(),t2.native_handle());
			}
			else {
				cg.resumeGame(t1.native_handle(),t2.native_handle());
				MOVING = temp;
			}
		}
		else {
			if (temp == 'Y') {
				cg.resetGame();
				cg.startGame();
			}
			else {
				cg.exitGame(t1.native_handle());
				t1.join();
				cg.exitGame(t2.native_handle());
				t2.join();
				return;
			}
		}
	}
}