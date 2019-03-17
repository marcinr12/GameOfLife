#pragma once
#include <iostream>
#include <vector>
#include <Windows.h>
#include <chrono>
#include "Cell.h"

using namespace std;
using namespace std::chrono;

class Grid
{
private:
	unsigned int sizeX = 0;
	unsigned int sizeY = 0;
	vector <vector<Cell>> cells;
	vector <vector<int>> previousStatus;

public:
	Grid() = delete;
	Grid(unsigned int, unsigned int);

	void printGrid();
	void navigate();
	unsigned int checkNeighbourhood(vector <vector<Cell>>, int, int, bool verticalCondition, bool horizontalCondition);
	void printStatus();
	void calculateNextGeneration(bool verticalCondition, bool horizontalConditiontion);
	void gotoxy(unsigned int, unsigned int);
	bool hasTimeElapsed(unsigned long, high_resolution_clock::time_point);
	void start(unsigned long, bool verticalCondition, bool horizontalCondition);

};