#pragma once
#include"CVEHICLE.h"
class CCAR :public CVEHICLE {
public:
	CCAR(int,int);
	void Draw();
	void Move();
	bool isCollide(int, int);
};