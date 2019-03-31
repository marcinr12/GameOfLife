#include "Grid.h"
#include "conio.h"
#include <chrono>



Grid::Grid(unsigned int sizeX, unsigned int sizeY)
{
	this->sizeX = sizeX;
	this->sizeY = sizeY;

	cells.resize(sizeX);
	previousStatus.resize(sizeX);
	for (int i = 0; i < sizeX; i++)
	{
		cells[i].resize(sizeY);
		previousStatus[i].resize(sizeY);
	}
		

	for (int i = 0; i < sizeX; i++)
	{
		for (int j = 0; j < sizeY; j++)
		{
			cells[i][j].setPossisionX(i);
			cells[i][j].setPossisionY(j);
			cells[i][j].setStatus(false);
			previousStatus[i][j] = -1;
		}
	}

	// consol coursor turning off
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(out, &cursorInfo);
}

vector<vector<Cell>> Grid::getCells()
{
	return cells;
}

shared_ptr<Cell> Grid::getCell(int x, int y)
{
	shared_ptr<Cell> cell = make_shared<Cell>(cells[x][y]);

	return cell;
}

Cell * Grid::getCellRaw(int x, int y)
{
	return &cells[x][y];
}


//void Grid::navigate()
//{
//	int x = 0;
//	int y = 0;
//
//	bool prevStatus = cellsStatus[x][y];
//	bool saved = false;
//
//	while (true)
//	{
//		printGrid();
//		if (saved == false)
//		{
//			prevStatus = cellsStatus[x][y];
//			saved = true;
//		}
//		cellsStatus[x][y] = !cellsStatus[x][y];
//		Sleep(300);
//
//		while ((GetAsyncKeyState(VK_RIGHT)) && y < sizeY - 1)
//		{
//			if (GetAsyncKeyState(VK_SPACE))
//				prevStatus = !prevStatus;
//			cellsStatus[x][y] = prevStatus;
//			saved = false;
//			y++;
//			Sleep(100);
//		}
//		while ((GetAsyncKeyState(VK_LEFT)) && y > 0)
//		{
//			if (GetAsyncKeyState(VK_SPACE))
//				prevStatus = !prevStatus;
//			cellsStatus[x][y] = prevStatus;
//			saved = false;
//			y--;
//			Sleep(100);
//		}
//		while (GetAsyncKeyState(VK_DOWN) && x < sizeX - 1)
//		{
//			if (GetAsyncKeyState(VK_SPACE))
//				prevStatus = !prevStatus;
//			cellsStatus[x][y] = prevStatus;
//			saved = false;
//			x++;
//			Sleep(100);
//		}
//
//		while (GetAsyncKeyState(VK_UP) && x > 0)
//		{
//			if (GetAsyncKeyState(VK_SPACE))
//				prevStatus = !prevStatus;
//			cellsStatus[x][y] = prevStatus;
//			saved = false;
//			x--;
//			Sleep(100);
//		}
//
//		if (GetAsyncKeyState(VK_RETURN))
//			break;
//
//	}
//}


void Grid::printGrid()
{

	gotoxy(0, 0);

	for (int i = 0; i < sizeX; i++)
	{
		for (int j = 0; j < sizeY; j++)
		{
			bool isAlive = cells[i][j].getStatus();

			gotoxy(i, j);
			if (isAlive != previousStatus[i][j] && isAlive == false)
				std::cout << char(176);
			else if (isAlive != previousStatus[i][j] && isAlive == true)
				std::cout << char(219);
			
		}
		std::cout << endl;

	}
}

void Grid::navigate()
{
	int x = 0;
	int y = 0;

	bool prevStatus = cells[x][y].getStatus();
	bool saved = false;											// checking if started status is saved

	char sign = 0;
	auto currentTimeNavigation = chrono::high_resolution_clock::now();
	auto currentTimeLoop = chrono::high_resolution_clock::now();

	unsigned long navigationInterval = 50;
	unsigned long loopInterval = 300;


	while (true)
	{
		if (x < 0)
			x = sizeX - 1;
		else if (x >= sizeX)
			x = 0;

		if (y < 0)
			y = sizeY - 1;
		else if (x >= sizeY)
			y = 0;

		if (_kbhit())			// save sign if it is avaiable 
		{
			sign = _getch();
		}

		if (hasTimeElapsed(loopInterval, currentTimeLoop) || (sign == 'a' || sign == 's' || sign == 'd' || sign == 'w' || sign == 'f' || sign == 'g'))
		{
			currentTimeLoop = chrono::high_resolution_clock::now();


			printGrid();

			if (saved == false)		// save starting status
			{
				prevStatus = cells[x][y].getStatus();
				saved = true;
			}
			cells[x][y].setStatus(!cells[x][y].getStatus());		// blinkind

			if (sign == 's' && hasTimeElapsed(navigationInterval, currentTimeNavigation))
			{
				cells[x][y].setStatus(prevStatus);
				sign = 0;
				y++;
				saved = false;
				auto currentTime = chrono::high_resolution_clock::now();
			}
			else if (sign == 'w' && hasTimeElapsed(navigationInterval, currentTimeNavigation))
			{
				cells[x][y].setStatus(prevStatus);
				sign = 0;
				y--;
				saved = false;
				auto currentTime = chrono::high_resolution_clock::now();
			}
			else if (sign == 'd' && hasTimeElapsed(navigationInterval, currentTimeNavigation))
			{
				cells[x][y].setStatus(prevStatus);
				sign = 0;
				x++;
				saved = false;
				auto currentTime = chrono::high_resolution_clock::now();
			}
			else if (sign == 'a' && hasTimeElapsed(navigationInterval, currentTimeNavigation))
			{
				cells[x][y].setStatus(prevStatus);
				sign = 0;
				x--;
				saved = false;
				auto currentTime = chrono::high_resolution_clock::now();
			}
			else if (sign == 'f' && hasTimeElapsed(navigationInterval, currentTimeNavigation))
			{
				cells[x][y].setStatus(!prevStatus);
				sign = 0;
				saved = false;
				auto currentTime = chrono::high_resolution_clock::now();
			}
			else if (sign == 'v')
			{
				cells[x][y].setStatus(!prevStatus);
				break;
			}
			else
				sign = 0;
		}
	}
}

unsigned int Grid::checkNeighbourhood(vector <vector<Cell>> cells, int x, int y, bool verticalCondition, bool horizontalCondition)
{
	unsigned int neighbours = 0;
	short int X[3] = { x - 1, x, x + 1 };
	short int Y[3] = { y - 1, y, y + 1 };

	// vertical condition
	if (verticalCondition)
	{
		if (x - 1 < 0)
			X[0] = sizeX - 1;
		if (X[2] == sizeX)
			X[2] = 0;
	}

	// horizontal condition 
	if (horizontalCondition)
	{
		if (y - 1 < 0)
			Y[0] = sizeY - 1;
		if (Y[2] == sizeY)
			Y[2] = 0;
	}


	if (X[0] >= 0 && Y[0] >= 0 && cells[X[0]][Y[0]].getStatus() == true)
		neighbours++;
	if (X[0] >= 0 && cells[X[0]][Y[1]].getStatus() == true)
		neighbours++;
	if (X[0] >= 0 && Y[2] < sizeY && cells[X[0]][Y[2]].getStatus() == true)
		neighbours++;

	if (Y[0] >= 0 && cells[X[1]][Y[0]].getStatus() == true)
		neighbours++;
	if (Y[2] < sizeY && cells[X[1]][Y[2]].getStatus() == true)
		neighbours++;

	if (X[2] < sizeX && Y[0] >= 0 && cells[X[2]][Y[0]].getStatus() == true)
		neighbours++;
	if (X[2] < sizeX && cells[X[2]][Y[1]].getStatus() == true)
		neighbours++;
	if (X[2] < sizeX && Y[2] < sizeY && cells[X[2]][Y[2]].getStatus() == true)
		neighbours++;

	return neighbours;
}

void Grid::printStatus()
{
	for (int i = 0; i < cells.size(); i++)
	{
		for (int j = 0; j < cells[0].size(); j++)
		{
			cout << cells[i][j].getStatus() << '\t';
		}
		cout << endl;
	}
}

void Grid::calculateNextGeneration(bool verticalCondition, bool horizontalCondition)
{
	vector<vector<Cell>> previous = cells;

	for (int i = 0; i < previous.size(); i++)
	{
		for (int j = 0; j < previous[0].size(); j++)
		{
			bool isAlive = previous[i][j].getStatus();
			previousStatus[i][j] = isAlive;							//saving status previous iteration to matrix 
			int neighbours = checkNeighbourhood(previous, i, j, verticalCondition, horizontalCondition);

			//if (neighbours < 2)
			//	cells[i][j].setStatus(false);
			//else if (isAlive == true && (neighbours == 3 || neighbours == 2))
			//	cells[i][j].setStatus(true);
			//else if (neighbours > 3)
			//	cells[i][j].setStatus(false);
			//else if (isAlive == false && neighbours == 3)
			//	cells[i][j].setStatus(true);


			if(neighbours == 3)
				cells[i][j].setStatus(true);
			else if(isAlive == true && neighbours ==2)
				cells[i][j].setStatus(true);
			else
				cells[i][j].setStatus(false);


		}
		cout << endl;
	}
}

void Grid::gotoxy(unsigned int x, unsigned int y)
{
	COORD c;

	c.X = x;
	c.Y = y;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

bool Grid::hasTimeElapsed(unsigned long millis, high_resolution_clock::time_point previousTime)
{
	auto currentTime = chrono::high_resolution_clock::now();
	auto timeElapsed = currentTime - previousTime;

	if (chrono::duration_cast<std::chrono::milliseconds>(timeElapsed).count() > millis)
	{
		return true;
	}
	return false;
}

void Grid::start(unsigned long interval, bool verticalCondition, bool horizontalCondition)
{
	auto currentTime = chrono::high_resolution_clock::now();
	while (true)
	{
		if (hasTimeElapsed(interval, currentTime))
		{
			currentTime = chrono::high_resolution_clock::now();
			calculateNextGeneration(verticalCondition, horizontalCondition);
			printGrid();
		}
		
	}
}
