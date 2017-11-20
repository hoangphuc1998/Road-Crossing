#include "CGAME.h"

int CGAME::getScore() {
	return score;
}
void CGAME::drawBoard() {
	//Ve canh tren
	GoToXY(0, 0);
	for (int i = 0; i <= width; i++) cout << 'X';
	//Ve canh duoi
	GoToXY(0, height);
	for (int i = 0; i <= width; i++) cout << 'X';
	//Ve 2 canh o 2 ben
	for (int i = 1; i < height; i++)
	{
		GoToXY(0, i); cout << 'X';
		GoToXY(width, i); cout << 'X';
	}
}

CGAME::CGAME() {
	cpe = new CPEOPLE();
	cob = new COBJECT*[height - 1];
	for (int i = 0; i < height - 1; i++) {
		cob[i] = NULL;
	}
	for (int i = 2; i < height - 1; i++) {
		int ob = rand() % 4;
		switch (ob){
		case 0:
			cob[i] = new CTRUCK(i);
			break;
		case 1:
			cob[i] = new CCAR(i);
			break;
		case 2:
			cob[i] = new CDINASAUR(i);
			break;
		case 3:
			cob[i] = new CBIRD(i);
			break;
		}
	}
}

/*CGAME::~CGAME() {
	for (int i = 2; i < height - 1; i++) {
		if (cob[i]!=NULL)
			delete cob[i];
	}
	delete[]cob;
}*/

void CGAME::drawGame() {
	for (int i = 2; i < height - 1; i++) {
		if (cob[i]!=NULL)
			cob[i]->Draw();
	}
	cpe->Draw();
	GoToXY(width + 6, height / 2);
	cout << "Score: " << score; 
	GoToXY(width + 6, height / 2+1);
	cout << "Press P to pause game";
}

COBJECT* CGAME::getObject(int y) {
	if(y>=2 && y<height-1)
		return cob[y];
	return NULL;
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
	for (int i = 2; i < height - 1; i++) {
		cob[i]->Move();
	}
}

void CGAME::resetGame() {
	cpe = new CPEOPLE();
	cob = new COBJECT*[height - 1];
	for (int i = 0; i < height - 1; i++) {
		cob[i] = NULL;
	}
	for (int i = 2; i < height - 1; i++) {
		int ob = rand() % 4;
		switch (ob) {
		case 0:
			cob[i] = new CTRUCK(i);
			break;
		case 1:
			cob[i] = new CCAR(i);
			break;
		case 2:
			cob[i] = new CDINASAUR(i);
			break;
		case 3:
			cob[i] = new CBIRD(i);
			break;
		}
	}
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
	GoToXY(width + 6, height / 2);
	cout << "Score: " << score;
	cpe->updateWhenFinish();
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
	for (int i = 2; i < height - 1; i++) {
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
	for (int i = 2; i < height - 1; i++) {
		fread(cob[i], sizeof(COBJECT), 1, f);
	}
	fclose(f);
	return true;
}