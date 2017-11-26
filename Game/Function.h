#pragma once
#ifndef FUNCTION_H
#define FUNCTION_H
#endif // !FUNCTION_H

#include <iostream>
#include <time.h>
using namespace std;
const int width = 68;
const int height = 20;

void FixConsoleWindow();
void GoToXY(int, int);
bool checkForLine(int y);