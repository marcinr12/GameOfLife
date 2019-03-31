#pragma once
#include <iostream>
#include <vector>
#include <Windows.h>
#include <memory>
#include <chrono>
#include "Cell.h"
#include <string>
#include "fileManagement.h"

using namespace std;
using namespace std::chrono;

class Grid
{
//private:
public:
	unsigned int sizeX = 0;
	unsigned int sizeY = 0;
	vector <vector<shared_ptr<Cell>>> cells;
	vector <vector<int>> previousStatus;

public:
	Grid() = delete;
	Grid(unsigned int, unsigned int);

	shared_ptr<Cell> getCell(int, int);
	unsigned int getSizeX();
	unsigned int getSizeY();

	void printGrid();
	void clearGrid();
	void navigate();
	unsigned int checkNeighbourhood(vector <vector<bool>>, int, int, bool verticalCondition, bool horizontalCondition);
	void calculateNextGeneration(bool verticalCondition, bool horizontalConditiontion);
	void gotoxy(unsigned int, unsigned int);
	bool hasTimeElapsed(unsigned long, high_resolution_clock::time_point);
	void start(unsigned long, bool verticalCondition, bool horizontalCondition);

	string encodeGrid();
	vector<vector<bool>> decodeGrid(string);
	void loadDecodedGrid(vector<vector<bool>>);
	
};