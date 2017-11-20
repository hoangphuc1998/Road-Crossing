#pragma once
#include "COBJECT.h"
class CVEHICLE :public COBJECT {
public:
	virtual ~CVEHICLE() {};
	CVEHICLE(int,char);
	void Tell();
};