#pragma once
#include "CANIMAL.h"
class CBIRD :public CANIMAL {
public:
	CBIRD(int,int);
	void Draw();
	void Move();
	bool isCollide(int, int);
};
