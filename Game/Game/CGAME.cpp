#include "CGAME.h"
#include "Function.h"

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
	srand(time(NULL));
	rowAnimal = new CANIMAL*[height - 1];
	rowVehicle = new CVEHICLE*[height - 1];
	for (int i = 0; i < height - 1; i++) {
		rowAnimal[i] = NULL;
		rowVehicle[i] = NULL;
	}
	for (int i = 1; i < height - 1; i++) {
		int ob = rand() % 4;
		if (ob == 0) {
			CTRUCK o();
			rowVehicle[i] = &o;

		}
	}
	drawBoard();
}

CGAME::~CGAME() {
	delete[]rowAnimal;
	delete[]rowVehicle;
}

