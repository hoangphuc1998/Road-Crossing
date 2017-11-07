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