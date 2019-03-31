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
			cells[i][j] = make_shared<Cell>(i, j, false);
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

shared_ptr<Cell> Grid::getCell(int x, int y)
{
	

	return this->cells[x][y];
}

unsigned int Grid::getSizeX()
{
	return sizeX;
}

unsigned int Grid::getSizeY()
{
	return sizeY;
}

void Grid::printGrid()
{

	gotoxy(0, 0);

	for (int i = 0; i < sizeX; i++)
	{
		for (int j = 0; j < sizeY; j++)
		{
			bool isAlive = cells[i][j]->getStatus();

			gotoxy(i, j);
			if (isAlive != previousStatus[i][j] && isAlive == false)
				std::cout << char(176);
			else if (isAlive != previousStatus[i][j] && isAlive == true)
				std::cout << char(219);
			
		}
		std::cout << endl;

	}
}

void Grid::clearGrid()
{
	for (int i = 0; i < sizeX; i++)
		for (int j = 0; j < sizeY; j++)
		{
			cells[i][j]->setStatus(false);
			previousStatus[i][j] = -1;
		}
			
}

void Grid::navigate()
{
	int x = 0;
	int y = 0;

	bool prevStatus = cells[x][y]->getStatus();
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
		else if (y >= sizeY)
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
				prevStatus = cells[x][y]->getStatus();
				saved = true;
			}
			cells[x][y]->setStatus(!cells[x][y]->getStatus());		// blinkind

			if (sign == 's' && hasTimeElapsed(navigationInterval, currentTimeNavigation))
			{
				cells[x][y]->setStatus(prevStatus);
				sign = 0;
				y++;
				saved = false;
				auto currentTime = chrono::high_resolution_clock::now();
			}
			else if (sign == 'w' && hasTimeElapsed(navigationInterval, currentTimeNavigation))
			{
				cells[x][y]->setStatus(prevStatus);
				sign = 0;
				y--;
				saved = false;
				auto currentTime = chrono::high_resolution_clock::now();
			}
			else if (sign == 'd' && hasTimeElapsed(navigationInterval, currentTimeNavigation))
			{
				cells[x][y]->setStatus(prevStatus);
				sign = 0;
				x++;
				saved = false;
				auto currentTime = chrono::high_resolution_clock::now();
			}
			else if (sign == 'a' && hasTimeElapsed(navigationInterval, currentTimeNavigation))
			{
				cells[x][y]->setStatus(prevStatus);
				sign = 0;
				x--;
				saved = false;
				auto currentTime = chrono::high_resolution_clock::now();
			}
			else if (sign == 'f' && hasTimeElapsed(navigationInterval, currentTimeNavigation))
			{
				cells[x][y]->setStatus(!prevStatus);
				sign = 0;
				saved = false;
				auto currentTime = chrono::high_resolution_clock::now();
			}
			else if (sign == 'v')
			{
				this->cells[x][y]->setStatus(prevStatus);
				break;
			}
			else
				sign = 0;
		}
	}
}

unsigned int Grid::checkNeighbourhood(vector <vector<bool>> cells, int x, int y, bool verticalCondition, bool horizontalCondition)
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


	if (X[0] >= 0 && Y[0] >= 0 && cells[X[0]][Y[0]] == true)
		neighbours++;
	if (X[0] >= 0 && cells[X[0]][Y[1]] == true)
		neighbours++;
	if (X[0] >= 0 && Y[2] < sizeY && cells[X[0]][Y[2]] == true)
		neighbours++;

	if (Y[0] >= 0 && cells[X[1]][Y[0]] == true)
		neighbours++;
	if (Y[2] < sizeY && cells[X[1]][Y[2]] == true)
		neighbours++;

	if (X[2] < sizeX && Y[0] >= 0 && cells[X[2]][Y[0]] == true)
		neighbours++;
	if (X[2] < sizeX && cells[X[2]][Y[1]] == true)
		neighbours++;
	if (X[2] < sizeX && Y[2] < sizeY && cells[X[2]][Y[2]] == true)
		neighbours++;

	return neighbours;
}

void Grid::calculateNextGeneration(bool verticalCondition, bool horizontalCondition)
{

	vector<vector<bool>> previous;
	previous.resize(cells.size());
	for (int i = 0; i < cells.size(); i++)
	{
		previous[i].resize(cells[i].size());
	}

	for (int i = 0; i < cells.size(); i++)
		for (int j = 0; j < cells[0].size(); j++)
			previous[i][j] = cells[i][j]->getStatus();

	for (int i = 0; i < previous.size(); i++)
	{
		for (int j = 0; j < previous[0].size(); j++)
		{
			bool isAlive = previous[i][j];
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


			if (neighbours == 3)
				this->getCell(i, j)->setStatus(1);
			else if (isAlive == true && neighbours == 2)
				this->getCell(i, j)->setStatus(1);
			else
				this->getCell(i, j)->setStatus(0);

			if (neighbours == 3)
			{
				cells[i][j]->setStatus(true);
			}
			else if (isAlive == true && neighbours == 2)
			{
				cells[i][j]->setStatus(true);
			}
			else
			{
				cells[i][j]->setStatus(false);
			}
			
		}
		std::cout << endl;
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
		char sign = 0;
		if (_kbhit())			// save sign if it is avaiable 
		{
			sign = _getch();
		}
		if (sign == 'p')
		{
			char s = 0;
			while (s != 'p')
			{
				s = _getch();
				if (s == 'f')
				{
					cout << "Encoded: " << encodeGrid() << endl;
					fileManagement::saveStateToFile(encodeGrid(), "abc");
				}
				if (s == 'l')
				{
					fs::path path{ fs::current_path().u8string() + "\\Saves\\abc" + ".rle" };
					string decoded = fileManagement::loadStateFromFile(path, sizeX, sizeY);
					vector<vector<bool>> v = decodeGrid(decoded);
					clearGrid();
					loadDecodedGrid(v);
					printGrid();
				}
				if (s == 'c')
				{
					clearGrid();
					printGrid();
				}
			}
		}
			
		if (hasTimeElapsed(interval, currentTime))
		{
			currentTime = chrono::high_resolution_clock::now();
			calculateNextGeneration(verticalCondition, horizontalCondition);
			printGrid();
		}
		
	}
}

string Grid::encodeGrid()
{
	string encoded = "";
	int counter = 0;
	int lastRow = 0;
	for (int i = 0; i < sizeX; i++)
	{
		for (int j = 0; j < sizeY; j++)
		{
			if (cells[i][j]->getStatus() == true && lastRow < j)
				lastRow = j;
		}
	}

	for (int i = 0; i <= lastRow; i++)
	{
		counter = 1;
		for (int j = 1; j < sizeX; j++)
		{
			if (cells[j - 1][i]->getStatus() == cells[j][i]->getStatus())
			{
				counter++;
			}
			else if (cells[j - 1][i]->getStatus() == true)
			{
				if (counter > 1)
					encoded += to_string(counter);
				encoded += 'o';
				counter = 1;
			}
			else if (cells[j - 1][i]->getStatus() == false)
			{
				if (counter > 1)
					encoded += to_string(counter);
				encoded += 'b';
				counter = 1;
			}
		}
		if (counter > 1)
			encoded += to_string(counter);
		if (cells[sizeY - 1][i]->getStatus() == true)
			encoded += 'o';
		else
			encoded += 'b';
		encoded += '$';
	}

	encoded.erase(encoded.length() - 1, 1);
	encoded.append("!");

	return encoded;
}

vector<vector<bool>> Grid::decodeGrid(string s)
{
	vector<vector<bool>> toReturn;
	toReturn.resize(sizeX);
	int row = 0;
	string counterString = "";
	for (int i = 0; i < s.length(); i++)
	{
		if (s[i] == '$')
		{
			row++;
		}
		else if(s[i] == 'b' || s[i] == 'o' || s[i] == '$')
		{
			bool state;
			if (s[i] == 'o')
				state = true;
			else
				state = false;

			int number = stoi(counterString);
			counterString = "";
			for (int j = 0; j < number; j++)
			{
				toReturn[row].push_back(state);
			}
		}
		else
		{
			counterString += s[i];
		}
	}
	return toReturn;
}

void Grid::loadDecodedGrid(vector<vector<bool>> v)
{
	for (int i = 0; i < v.size(); i++)
		for (int j = 0; j < v[i].size(); j++)
			cells[j][i]->setStatus(v[i][j]);
}
