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
	//Ve khung hien thi ten tro choi
	GoToXY(0, height+2);
	cout << (char)201;
	for (int i = 1; i < 16; i++) cout << (char)205;
	cout << (char)187;
	//Ve canh duoi
	GoToXY(0, height+4);
	cout << (char)200;
	for (int i = 1; i < 16; i++) cout << (char)205;
	cout << (char)188;
	//Ve 2 canh o 2 ben
	for (int i = height+3; i < height+4; i++)
	{
		GoToXY(0, i); cout << (char)186;
		GoToXY(16, i); cout << (char)186;
	}

	GoToXY(2, height + 3);
	cout << "ROAD CROSSING";
	GoToXY(width / 2-10, height + 2);
	cout << "Press P to pause game";
	GoToXY(width / 2-10, height + 3);
	cout << "Press ESC to exit";

	//Ve khung hien thi diem
	GoToXY(width-16, height + 2);
	cout << (char)201;
	for (int i = width - 16; i < width-1; i++) cout << (char)205;
	cout << (char)187;
	//Ve canh duoi
	GoToXY(width - 16, height + 5);
	cout << (char)200;
	for (int i = width - 16; i < width-1; i++) cout << (char)205;
	cout << (char)188;
	//Ve 2 canh o 2 ben
	for (int i = height + 3; i < height + 5; i++)
	{
		GoToXY(width-16, i); cout << (char)186;
		GoToXY(width, i); cout << (char)186;
	}
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
	GoToXY(width-14, height+3);
	cout << "Score: " << score; 
	GoToXY(width - 14, height + 4);
	cout << "Level: " << score%8+1;
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
	cout << "	          uuuuuuu" << endl;
	cout << "             uu$$$$$$$$$$$uu" << endl;
	cout << "          uu$$$$$$$$$$$$$$$$$uu" << endl;
	cout << "         u$$$$$$$$$$$$$$$$$$$$$u" << endl;
	cout << "        u$$$$$$$$$$$$$$$$$$$$$$$u" << endl;
	cout << "       u$$$$$$$$$$$$$$$$$$$$$$$$$u" << endl;
	cout << "       u$$$$$$$$$$$$$$$$$$$$$$$$$u" << endl;
	cout << "       u$$$$$$\"   \"$$$\"   \"$$$$$$u" << endl;
	cout << "       \"$$$$\"      u$u       $$$$\""<<endl;
	cout << "        $$$u       u$u       u$$$" << endl;
	cout << "        $$$u      u$$$u      u$$$" << endl;
	cout << "         \"$$$$uu$$$   $$$uu$$$$\"" << endl;
	cout << "          \"$$$$$$$\"   \"$$$$$$$\"" << endl;
	cout << "            u$$$$$$$u$$$$$$$u" << endl;
	cout << "             u$\"$\"$\"$\"$\"$\"$u" << endl;
	cout << "  uuu        $$u$ $ $ $ $u$$       uuu" << endl;
	cout << " u$$$$        $$$$$u$u$u$$$       u$$$$" << endl;
	cout << "  $$$$$uu      \"$$$$$$$$$\"     uu$$$$$$" << endl;
	cout << "u$$$$$$$$$$$uu    \"\"\"\"\"    uuuu$$$$$$$$$$" << endl;
	cout << "$$$$\"\"\"$$$$$$$$$$uuu   uu$$$$$$$$$\"\"\"$$$\"" << endl;
	cout << " \"\"\"      \"\"$$$$$$$$$$$uu \"\"$\"\"\"" << endl;
	cout << "           uuuu \"\"$$$$$$$$$$uuu" << endl;
	cout << "  u$$$uuu$$$$$$$$$uu \"\"$$$$$$$$$$$uuu$$$" << endl;
	cout << "  $$$$$$$$$$\"\"\"\"           \"\"$$$$$$$$$$$\"" << endl;
	cout << "   \"$$$$$\"                      \"\"$$$$\"\"" << endl;
	cout << "     $$$\"                         $$$$\"" << endl;
	
	CONSOLE_SCREEN_BUFFER_INFO info;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsole, &info);
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
	int mX = width / 2 + 10;
	int mY = height / 2;
	GoToXY(mX + 7, mY - 5);
	cout << "YOU DEAD";
	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
	//Ve khung vien
	GoToXY(mX-2, mY - 1);
	cout << (char)201;
	for (int i = 1; i < 25; i++) cout << (char)205;
	cout << (char)187;
	//Ve canh duoi
	GoToXY(mX - 2, mY + 3);
	cout << (char)200;
	for (int i = 1; i < 25; i++) cout << (char)205;
	cout << (char)188;
	//Ve 2 canh o 2 ben
	for (int i = mY; i < mY + 3; i++)
	{
		GoToXY(mX - 2, i); cout << (char)186;
		GoToXY(mX + 23, i); cout << (char)186;
	}
	GoToXY(mX, mY);
	cout << "SCORE: " << score;
	GoToXY(mX, mY+1);
	cout << "Press Y to restart";
	GoToXY(mX, mY + 2);
	cout << "Press any key to exit";
	SetConsoleTextAttribute(hConsole, info.wAttributes);
	PlaySound(TEXT("crash.wav"), NULL, SND_FILENAME);
}

void CGAME::pauseGame(HANDLE t,HANDLE t2) {
	SuspendThread(t);
	SuspendThread(t2);
	system("cls");
	DrawGameName();
	int mX = width / 2 - 5;
	int mY = 15;
	GoToXY(mX-5, mY - 1);
	cout << (char)201;
	for (int i = 1; i < 18; i++) cout << (char)205;
	cout << (char)187;
	//Ve canh duoi
	GoToXY(mX-5, mY + 3);
	cout << (char)200;
	for (int i = 1; i < 18; i++) cout << (char)205;
	cout << (char)188;
	//Ve 2 canh o 2 ben
	for (int i = mY; i < mY + 3; i++)
	{
		GoToXY(mX-5, i); cout << (char)186;
		GoToXY(mX + 13, i); cout << (char)186;
	}
	GoToXY(mX, mY);
	cout << "1. Continue";
	GoToXY(mX, mY+1);
	cout << "2. Save Game";
	GoToXY(mX, mY+2);
	cout << "3. Load Game";
	GoToXY(mX - 3, mY);
	cout << "->";
	int choose = 1;
	int temp = toupper(_getch());
	while (temp != 13) {
		if (temp == 'W') {
			if (choose == 2) {
				GoToXY(mX - 3, mY);
				cout << "->";
				GoToXY(mX - 3, mY + 1);
				cout << "  ";
				choose = 1;
			}
			else if (choose == 3) {
				GoToXY(mX - 3, mY + 1);
				cout << "->";
				GoToXY(mX - 3, mY + 2);
				cout << "  ";
				choose = 2;
			}
		}
		if (temp == 'S') {
			if (choose == 1) {
				GoToXY(mX - 3, mY + 1);
				cout << "->";
				GoToXY(mX - 3, mY);
				cout << "  ";
				choose = 2;
			}
			else if (choose == 2) {
				GoToXY(mX - 3, mY + 2);
				cout << "->";
				GoToXY(mX - 3, mY + 1);
				cout << "  ";
				choose = 3;
			}
		}
		temp = toupper(_getch());
	}
	system("cls");
	DrawGameName();
	if (choose != 1) {
		char s[100];
		GoToXY(mX, mY);
		cout << "Enter file name: ";
		fgets(s, 101, stdin);
		s[strlen(s)-1] = '\0';
		system("cls");
		if (choose == 2) {
			bool kt = saveGame(s);
			if (kt) {
				DrawGameName();
				GoToXY(mX, mY);
				cout << "Save successful";
				GoToXY(mX, mY+1);
				system("pause");
			}
			else {
				DrawGameName();
				GoToXY(mX, mY);
				cout << "Save failed";
				GoToXY(mX, mY + 1);
				system("pause");
			}
		}
		else {
			bool kt = loadGame(s);
			if (kt) {
				DrawGameName();
				GoToXY(mX, mY);
				cout << "Load successful";
				GoToXY(mX, mY + 1);
				system("pause");
			}
			else {
				DrawGameName();
				GoToXY(mX, mY);
				cout << "Load failed";
				GoToXY(mX, mY + 1);
				system("pause");
			}
		}
	}
	startGame();
}

void CGAME::DrawMenuWhenStart() {
	system("cls");
	DrawGameName();
	int mX = width / 2 - 5;
	int mY = 15;
	GoToXY(mX, mY-1);
	cout << (char)201;
	for (int i = 1; i < 18; i++) cout << (char)205;
	cout << (char)187;
	//Ve canh duoi
	GoToXY(mX, mY + 3);
	cout << (char)200;
	for (int i = 1; i < 18; i++) cout << (char)205;
	cout << (char)188;
	//Ve 2 canh o 2 ben
	for (int i = mY; i < mY + 3; i++)
	{
		GoToXY(mX, i); cout << (char)186;
		GoToXY(mX+18, i); cout << (char)186;
	}
	GoToXY(width / 2, mY);
	cout << "1. New Game";
	GoToXY(width / 2, mY+1);
	cout << "2. Load Game";
	GoToXY(width / 2, mY+2);
	cout << "3. Settings";
	GoToXY(width / 2-3, mY);
	cout << "->";
	int temp;
	temp = toupper(_getch());
	int choose = 1;
	while (temp != 13) {
		if (temp == 'W') {
			if (choose == 2) {
				GoToXY(width / 2 - 3, mY);
				cout << "->";
				GoToXY(width / 2 - 3, mY + 1);
				cout << "  ";
				choose = 1;
			}
			else if (choose == 3) {
				GoToXY(width / 2 - 3, mY + 1);
				cout << "->";
				GoToXY(width / 2 - 3, mY + 2);
				cout << "  ";
				choose = 2;
			}
		}
		if (temp == 'S') {
			if (choose == 1) {
				GoToXY(width / 2 - 3, mY + 1);
				cout << "->";
				GoToXY(width / 2 - 3, mY);
				cout << "  ";
				choose = 2;
			}
			else if (choose == 2) {
				GoToXY(width / 2 - 3, mY + 2);
				cout << "->";
				GoToXY(width / 2 - 3,mY + 1);
				cout << "  ";
				choose = 3;
			}
		}
		temp = toupper(_getch());
	}
	if (choose == 2) {
		system("cls");
		DrawGameName();
		char s[100];
		GoToXY(mX, mY);
		cout << "Enter file name: ";
		fgets(s, 101, stdin);
		s[strlen(s) - 1] = '\0';
		system("cls");
		DrawGameName();
		bool kt = loadGame(s);
		if (kt) {
			GoToXY(mX, mY);
			cout << "Load successful";
			GoToXY(mX, mY + 1);
			system("pause");
		}
		else {
			GoToXY(mX, mY);
			cout << "Load failed";
			GoToXY(mX, mY + 1);
			system("pause");
		}
	}
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

void CGAME::DrawGameName() {
	GoToXY(0, 0);
	cout << "  ____   ___    _    ____     ____ ____   ___  ____ ____ ___ _   _  ____ " << endl;
	cout << " |  _ \\ / _ \\  / \\  |  _ \\   / ___|  _ \\ / _ \\/ ___/ ___|_ _| \\ | |/ ___|" << endl;
	cout << " | |_) | | | |/ _ \\ | | | | | |   | |_) | | | \\___ \\___ \\| ||  \\| | |  _ " << endl;
	cout << " |  _ <| |_| / ___ \\| |_| | | |___|  _ <| |_| |___) |__) | || |\\  | |_| |" << endl;
	cout << " |_| \\_\\\\___/_/   \\_\\____/   \\____|_| \\_\\\\___/|____/____/___|_| \\_|\\____|" << endl;
	//Draw Truck
	int mX = 15;
	int mY = 8;
	GoToXY(mX, mY);
	cout << (char)219;
	GoToXY(mX + 1, mY);
	cout << (char)219;
	GoToXY(mX + 1, mY - 1);
	cout << (char)219;
	GoToXY(mX + 2, mY);
	cout << (char)219;
	GoToXY(mX + 2, mY - 1);
	cout << (char)219;
	//Draw car
	mX += 15;
	GoToXY(mX, mY);
	cout << (char)219;
	GoToXY(mX + 1, mY);
	cout << (char)219;
	GoToXY(mX + 1, mY - 1);
	cout << (char)219;
	GoToXY(mX + 2, mY);
	cout << (char)219;
	//Draw bird
	mX += 15;
	GoToXY(mX, mY - 1);
	cout << (char)219;
	GoToXY(mX + 1, mY);
	cout << (char)219;
	GoToXY(mX + 2, mY - 1);
	cout << (char)219;
	//Draw dinosaur
	mX += 15;
	GoToXY(mX, mY);
	cout << (char)219;
	GoToXY(mX + 1, mY);
	cout << (char)219;
	GoToXY(mX + 1, mY - 1);
	cout << (char)219;
	GoToXY(mX + 2, mY - 2);
	cout << (char)219;
	GoToXY(mX + 2, mY - 1);
	cout << (char)219;
}