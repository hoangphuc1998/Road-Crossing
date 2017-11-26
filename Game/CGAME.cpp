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
	mLight1 = new CTRAFFICLIGHT(50, width + 2, height - 6);
	mLight2 = new CTRAFFICLIGHT(30, width + 2, height - 10);
}


void CGAME::drawGame() {
	for (int i = 0; i < cob.size(); i++) {
		cob[i]->Draw();
	}
	cpe->Draw();
	GoToXY(width/2, height+5);
	cout << "Score: " << score; 
	GoToXY(width/2, height+6);
	cout << "Press P to pause game";
	mLight1->drawWhenStart();
	mLight2->drawWhenStart();
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
		if (i % 4 == 0 && mLight1->isRed()==true) {
			continue;
		}
		else if (i % 4 == 1 && mLight2->isRed()==true) {
			continue;
		}
		else {
			cob[i]->Move();
		}
	}
}

void CGAME::resetGame() {
	if(cpe!=NULL) delete cpe;
	if(mLight1!=NULL)delete mLight1;
	if(mLight2!=NULL) delete mLight2;
	cpe = new CPEOPLE();
	cob.clear();
	cob.push_back(new CTRUCK(width / 2, 17));
	cob.push_back(new CCAR(width / 2, 13));
	cob.push_back(new CBIRD(width / 2, 8));
	cob.push_back(new CDINASAUR(width / 2, 5));
	mLight1 = new CTRAFFICLIGHT(50, width + 2, height - 6);
	mLight2 = new CTRAFFICLIGHT(30, width + 2, height - 10);
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

void CGAME::resumeGame(HANDLE t,HANDLE t2) {
	ResumeThread(t);
	ResumeThread(t2);
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

void CGAME::pauseGame(HANDLE t,HANDLE t2) {
	SuspendThread(t);
	SuspendThread(t2);
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
	FILE* f = fopen(filename, "w");
	if (f == NULL) return false;
	fprintf(f, "%d ", score);
	fprintf(f, "%d %d ", cpe->getX(), cpe->getY());
	for (int i = 0; i < (score%8+1)*4; i++) {
		fprintf(f, "%d %d ", cob[i]->getX(), cob[i]->getY());
	}
	mLight1->save(f);
	mLight2->save(f);
	fclose(f);
	return true;
}

bool CGAME::loadGame(char *filename) {
	FILE* f = fopen(filename, "r");
	if (f == NULL) return false;
	fscanf(f, "%d ", &score);
	int x, y;
	fscanf(f, "%d %d ", &x,&y);
	delete cpe;
	cpe = new CPEOPLE(x, y);
	cob.clear();
	for (int i = 0; i < score+1; i++) {
		fscanf(f, "%d %d ", &x, &y);
		cob.push_back(new CTRUCK(x, y));
		fscanf(f, "%d %d ", &x, &y);
		cob.push_back(new CCAR(x, y));
		fscanf(f, "%d %d ", &x, &y);
		cob.push_back(new CBIRD(x, y));
		fscanf(f, "%d %d ", &x, &y);
		cob.push_back(new CDINASAUR(x, y));
	}
	mLight1->load(f);
	mLight2->load(f);
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

void CGAME::updateTrafficLight() {
	mLight1->updateTime();
	mLight2->updateTime();
}