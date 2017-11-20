#pragma once
#include"CVEHICLE.h"
class CTRUCK :public CVEHICLE {
public:
	void Draw();
	void Move();
	bool isCollide(int,int);
	CTRUCK(int,int);
};