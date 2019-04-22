#pragma once
#include <SFML/Graphics.hpp>

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
using namespace sf;

class Grid
{

	unsigned int sizeX = 0;
	unsigned int sizeY = 0;
	unsigned int gridWindowHeight = 0;
	unsigned int gridWindowWidth = 0;
	vector <vector<shared_ptr<Cell>>> cells;
	vector <vector<int>> previousStatus;

public:
	Grid() = delete;
	Grid(unsigned int sizeX, unsigned int sizeY);
	Grid(unsigned int sizeX, unsigned int sizeY, unsigned int gridWindowWidth, unsigned int gridWindowHeight);

	shared_ptr<Cell> getCell(int, int);
	unsigned int getSizeX();
	unsigned int getSizeY();

	void printGridSFML(RenderWindow&);
	void clearGrid();
	unsigned int checkNeighbourhood(vector <vector<bool>>, int, int, bool verticalCondition, bool horizontalCondition);
	void calculateNextGeneration(bool verticalCondition, bool horizontalConditiontion);
	void oneGenerationBack();

	string encodeGrid();
	vector<vector<bool>> decodeGrid(string);
	void loadDecodedGrid(vector<vector<bool>>);
	
};