#pragma once
#include "COBJECT.h"
class CANIMAL:public COBJECT {
public:
	virtual ~CANIMAL() {};
	CANIMAL(int,char);
	virtual void Tell()=0;
};