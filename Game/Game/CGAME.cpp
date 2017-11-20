#include "CGAME.h"


void CGAME::drawBoard() {
	//Ve canh tren
	GoToXY(0, 0);
	cout << (char)201;
	for (int i = 1; i < width; i++) cout << (char)205;
	cout << (char)187;
	//Ve canh duoi
	GoToXY(0, height);
	cout << (char)200;
	for (int i = 1; i < width; i++) cout << (char)205;
	cout << (char)188;
	//Ve 2 canh o 2 ben
	for (int i = 1; i < height; i++)
	{
		GoToXY(0, i); cout << (char)186;
		GoToXY(width, i); cout << (char)186;
	}
	GoToXY(1, 1);
	for (int i = 1; i < width; i++) cout << (char)95;
	GoToXY(1, 5);
	for (int i = 1; i < width; i++) cout << (char)95;
	GoToXY(1, 9);
	for (int i = 1; i < width; i++) cout << (char)95;
	GoToXY(1, 13);
	for (int i = 1; i < width; i++) cout << (char)95;
	GoToXY(1, 17);
	for (int i = 1; i < width; i++) cout << (char)95;
}

CGAME::CGAME() {
	score = 0;
	cpe = new CPEOPLE();
	cob.clear();
	cob.push_back(new CTRUCK(width / 2, 17));
	cob.push_back(new CCAR(width / 2, 13));
	cob.push_back(new CBIRD(width / 2, 8));
	cob.push_back(new CDINASAUR(width / 2, 5));
}



void CGAME::drawGame() {
	for (int i = 0; i < cob.size(); i++) {
		cob[i]->Draw();
	}
	cpe->Draw();
	GoToXY(width + 6, height / 2);
	cout << "Score: " << score; 
	GoToXY(width + 6, height / 2+1);
	cout << "Press P to pause game";
}


CPEOPLE* CGAME::getPeople() {
	return cpe;
}

void CGAME::updatePosPeople(char move) {
	switch (move) {
	case 'W':
		cpe->Up();
		break;
	case 'S':
		cpe->Down();
		break;
	case 'D':
		cpe->Right();
		break;
	case 'A':
		cpe->Left();
		break;
	default:
		return;
	}
}

void CGAME::updatePosObject() {
	for (int i = 0; i < cob.size(); i++) {
		cob[i]->Move();
	}
}

void CGAME::resetGame() {
	cpe = new CPEOPLE();
	cob.clear();
	cob.push_back(new CTRUCK(width / 2, 17));
	cob.push_back(new CCAR(width / 2, 13));
	cob.push_back(new CBIRD(width / 2, 8));
	cob.push_back(new CDINASAUR(width / 2, 5));
	score = 0;
}

void CGAME::startGame() {
	system("cls");
	drawBoard();
	drawGame();
}

void CGAME::exitGame(HANDLE t) {
	system("cls");
	TerminateThread(t, 0);
}

void CGAME::resumeGame(HANDLE t) {
	ResumeThread(t);
}

void CGAME::increaseScore() {
	score++;
	cpe->updateWhenFinish();
	if (score % 8 != 0) {
		cob.push_back(new CTRUCK(cob[(score-1) % 8 * 4]->getNewX(), 17));
		cob.push_back(new CCAR(cob[(score - 1) % 8 * 4 + 1]->getNewX(), 13));
		cob.push_back(new CBIRD(cob[(score - 1) % 8 * 4 + 2]->getNewX(), 8));
		cob.push_back(new CDINASAUR(cob[(score - 1) % 8 * 4 + 3]->getNewX(), 5));
		drawGame();
	}
	else {
		cob.clear();
		cob.push_back(new CTRUCK(width / 2, 17));
		cob.push_back(new CCAR(width / 2, 13));
		cob.push_back(new CBIRD(width / 2, 8));
		cob.push_back(new CDINASAUR(width / 2, 5));
		startGame();
	}
	
}

void CGAME::updateWhenDie() {
	system("cls");
	GoToXY(width / 2, height / 2);
	cout << "SCORE: " << score;
	GoToXY(width / 2, height / 2+1);
	cout << "Press Y to restart";
	GoToXY(width / 2, height / 2 + 2);
	cout << "Press any key to exit";
}

void CGAME::pauseGame(HANDLE t) {
	SuspendThread(t);
	system("cls");
	GoToXY(width / 2, height / 2);
	cout << "1. Continue";
	GoToXY(width / 2, height / 2+1);
	cout << "2. Save Game";
	GoToXY(width / 2, height / 2+2);
	cout << "3. Load Game";
	GoToXY(width / 2 - 3, height / 2);
	cout << "->";
	int choose = 1;
	int temp = toupper(_getch());
	while (temp != 13) {
		if (temp == 'W') {
			if (choose == 2) {
				GoToXY(width / 2 - 3, height / 2);
				cout << "->";
				GoToXY(width / 2 - 3, height / 2 + 1);
				cout << "  ";
				choose = 1;
			}
			else if (choose == 3) {
				GoToXY(width / 2 - 3, height / 2 + 1);
				cout << "->";
				GoToXY(width / 2 - 3, height / 2 + 2);
				cout << "  ";
				choose = 2;
			}
		}
		if (temp == 'S') {
			if (choose == 1) {
				GoToXY(width / 2 - 3, height / 2 + 1);
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
	system("cls");
	if (choose != 1) {
		char s[100];
		GoToXY(width / 2, height / 2);
		cout << "Enter file name: ";
		fgets(s, 101, stdin);
		s[strlen(s)-1] = '\0';
		system("cls");
		if (choose == 2) {
			bool kt = saveGame(s);
			if (kt) {
				GoToXY(width / 2, height / 2);
				cout << "Save successful";
				GoToXY(width / 2, height / 2+1);
				system("pause");
			}
			else {
				GoToXY(width / 2, height / 2);
				cout << "Save failed";
				GoToXY(width / 2, height / 2 + 1);
				system("pause");
			}
		}
		else {
			bool kt = loadGame(s);
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
	}
	startGame();
}

void CGAME::DrawMenuWhenStart() {
	system("cls");
	GoToXY(width / 2, height / 2);
	cout << "1. New Game";
	GoToXY(width / 2, height / 2 + 1);
	cout << "2. Load Game";
	GoToXY(width / 2, height / 2 + 2);
	cout << "3. Settings";
	GoToXY(width / 2-3, height / 2);
	cout << "->";
	GoToXY(width / 2, height / 2 + 4);
	cout << "Press W to move Up, S to move Down, ENTER to choose";
}

bool CGAME::saveGame(char* filename) {
	FILE* f = fopen(filename, "wb");
	if (f == NULL) return false;
	fwrite(&score, sizeof(int), 1, f);
	fwrite(cpe, sizeof(CPEOPLE), 1, f);
	for (int i = 0; i < (score%8+1)*4; i++) {
		fwrite(cob[i], sizeof(COBJECT), 1, f);
	}
	fclose(f);
	return true;
}

bool CGAME::loadGame(char *filename) {
	FILE* f = fopen(filename, "rb");
	if (f == NULL) return false;
	fread(&score, sizeof(int), 1, f);
	fread(cpe, sizeof(CPEOPLE), 1, f);
	cob.clear();
	for (int i = 0; i < (score%8+1)*4; i++) {
		COBJECT * p = NULL;
		fread(p, sizeof(COBJECT), 1, f);
		cob.push_back(p);
	}
	fclose(f);
	return true;
}

bool CGAME::isPeopleCrash() {
	for (int i = 0; i < cob.size(); i++) {
		if (cob[i]->isCollide(cpe->getX(), cpe->getY())) {
			return true;
		}
	}
	return false;
}