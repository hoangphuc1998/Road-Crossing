#pragma once
#include "CANIMAL.h"
class CDINASAUR :public CANIMAL {
public:
	CDINASAUR(int,int);
	void Draw();
	void Move();
	bool isCollide(int, int);
};