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

Grid::Grid(unsigned int sizeX, unsigned int sizeY, unsigned int windowHeight, unsigned int windowWidth)
{
	this->sizeX = sizeX;
	this->sizeY = sizeY;
	double dX = (windowWidth * 1.0) / sizeX;
	double dY = (windowHeight * 1.0) / sizeY;

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
			cells[i][j] = make_shared<Cell>(i * dX, j * dY, false);
			previousStatus[i][j] = -1;
		}
	}
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

void Grid::printGridSFML(RenderWindow &appWindow, unsigned int windowSizeX, unsigned int windowSizeY)
{
	for (int i = 0; i < sizeX; i++)
	{
		for (int j = 0; j < sizeY; j++)
		{
			sf::RectangleShape rs;
			rs.setPosition(sf::Vector2f(windowSizeX * 1.0 / sizeX * i, windowSizeY * 1.0 / sizeY * j));
			rs.setSize(sf::Vector2f(windowSizeX * 1.0 / sizeX, windowSizeY * 1.0 / sizeY));
			rs.setOutlineThickness(0.5);
			rs.setOutlineColor(sf::Color(125, 125, 125, 40));
			if (cells[i][j]->getStatus() == true)
			{
				rs.setFillColor(Color::Green);
			}
			else 
				rs.setFillColor(Color::Black);

			appWindow.draw(rs);
		}
	}
}

void Grid::eventListeners(RenderWindow& appWindow, Event& event)
{
	while (appWindow.pollEvent(event))
	{
		if (event.type == Event::Closed)
			appWindow.close();
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
	}
}

void Grid::oneGenerationBack()
{
	for (int i = 0; i < sizeX; i++)
	{
		for (int j = 0; j < sizeY; j++)
		{
			bool tmp = previousStatus[i][j];
			if (tmp != -1)
			{
				previousStatus[i][j] = cells[i][j]->getStatus();
				cells[i][j]->setStatus(tmp);
			}
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
