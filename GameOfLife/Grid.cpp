#include "Grid.h"
#include "conio.h"
#include <chrono>

Grid::Grid(unsigned int sizeX, unsigned int sizeY)
{
	this->sizeX = sizeX;
	this->sizeY = sizeY;

	this->cells.resize(sizeX);
	this->previousStatus.resize(sizeX);
	for (int i = 0; i < sizeX; i++)
	{
		this->cells[i].resize(sizeY);
		this->previousStatus[i].resize(sizeY);
	}
		

	for (int i = 0; i < sizeX; i++)
	{
		for (int j = 0; j < sizeY; j++)
		{
			this->cells[i][j] = make_shared<Cell>(i, j, false);
			this->previousStatus[i][j] = -1;
		}
	}
}

Grid::Grid(unsigned int sizeX, unsigned int sizeY, unsigned int gridWindowWidth, unsigned int gridWindowHeight)
{
	this->sizeX = sizeX;
	this->sizeY = sizeY;
	double dX = (gridWindowWidth * 1.0) / sizeX;
	double dY = (gridWindowHeight * 1.0) / sizeY;
	this->gridWindowHeight = gridWindowHeight;
	this->gridWindowWidth = gridWindowWidth;
	this->vertexArray = VertexArray(Quads);
	this->vertexArray.resize(4 * sizeX * sizeY);

	this->cells.resize(sizeX);
	this->previousStatus.resize(sizeX);
	for (int i = 0; i < sizeX; i++)
	{
		this->cells[i].resize(sizeY);
		this->previousStatus[i].resize(sizeY);
	}

	for (int i = 0; i < sizeX; i++)
	{
		for (int j = 0; j < sizeY; j++)
		{
			this->cells[i][j] = make_shared<Cell>(i * dX, j * dY, false);
			this->previousStatus[i][j] = -1;
		}
	}
}

shared_ptr<Cell> Grid::getCell(int x, int y)
{

	return this->cells[x][y];
}

unsigned int Grid::getSizeX()
{
	return this->sizeX;
}

unsigned int Grid::getSizeY()
{
	return this->sizeY;
}

void Grid::printGridSFML(RenderWindow &appWindow)
{
	for (int i = 0; i < sizeX; i++)
	{
		for (int j = 0; j < sizeY; j++)
		{
			this->vertexArray[(i * sizeY + j) * 4].position = sf::Vector2f(gridWindowWidth * 1.0 / sizeX * i, gridWindowHeight * 1.0 / sizeY * j);
			this->vertexArray[(i * sizeY + j) * 4 + 1].position = sf::Vector2f(gridWindowWidth * 1.0 / sizeX * (i + 1), gridWindowHeight * 1.0 / sizeY * j);
			this->vertexArray[(i * sizeY + j) * 4 + 2].position = sf::Vector2f(gridWindowWidth * 1.0 / sizeX * (i + 1), gridWindowHeight * 1.0 / sizeY * (j + 1));
			this->vertexArray[(i * sizeY + j) * 4 + 3].position = sf::Vector2f(gridWindowWidth * 1.0 / sizeX * i, gridWindowHeight * 1.0 / sizeY * (j + 1));


			if (cells[i][j]->getStatus() == true)
			{
				//vertexArray[(i * sizeY + j) * 4].color = Color::Green;
				//vertexArray[(i * sizeY + j) * 4 + 1].color = Color::Green;
				//vertexArray[(i * sizeY + j) * 4 + 2].color = Color::Green;
				//vertexArray[(i * sizeY + j) * 4 + 3].color = Color::Green;
				this->vertexArray[(i * sizeY + j) * 4].color = Color::Black;
				this->vertexArray[(i * sizeY + j) * 4 + 1].color = Color::Green;
				this->vertexArray[(i * sizeY + j) * 4 + 2].color = Color::Green;
				this->vertexArray[(i * sizeY + j) * 4 + 3].color = Color::Green;
			}
			else
			{
				this->vertexArray[(i * sizeY + j) * 4].color = Color::Red;
				this->vertexArray[(i * sizeY + j) * 4 + 1].color = Color::Black;
				this->vertexArray[(i * sizeY + j) * 4 + 2].color = Color::Black;
				this->vertexArray[(i * sizeY + j) * 4 + 3].color = Color::Black;
			}	
		}
	}
	appWindow.draw(vertexArray);
}

void Grid::clearGrid()
{
	for (int i = 0; i < sizeX; i++)
		for (int j = 0; j < sizeY; j++)
		{
			this->cells[i][j]->setStatus(false);
			this->previousStatus[i][j] = -1;
		}
			
}

unsigned int Grid::checkNeighbourhood(vector <vector<bool>> & cells, int x, int y, bool verticalCondition, bool horizontalCondition)
{
	unsigned int neighbours = 0;
	short int X[3] = { x - 1, x, x + 1 };
	short int Y[3] = { y - 1, y, y + 1 };

	// vertical condition
	if (verticalCondition)
	{
		if (x - 1 < 0)
			X[0] = this->sizeX - 1;
		if (X[2] == this->sizeX)
			X[2] = 0;
	}

	// horizontal condition 
	if (horizontalCondition)
	{
		if (y - 1 < 0)
			Y[0] = this->sizeY - 1;
		if (Y[2] == this->sizeY)
			Y[2] = 0;
	}


	if (X[0] >= 0 && Y[0] >= 0 && cells[X[0]][Y[0]] == true)
		neighbours++;
	if (X[0] >= 0 && cells[X[0]][Y[1]] == true)
		neighbours++;
	if (X[0] >= 0 && Y[2] < this->sizeY && cells[X[0]][Y[2]] == true)
		neighbours++;

	if (Y[0] >= 0 && cells[X[1]][Y[0]] == true)
		neighbours++;
	if (Y[2] < this->sizeY && cells[X[1]][Y[2]] == true)
		neighbours++;

	if (X[2] < this->sizeX && Y[0] >= 0 && cells[X[2]][Y[0]] == true)
		neighbours++;
	if (X[2] < this->sizeX && cells[X[2]][Y[1]] == true)
		neighbours++;
	if (X[2] < this->sizeX && Y[2] < this->sizeY && cells[X[2]][Y[2]] == true)
		neighbours++;

	return neighbours;
}

vector<vector<unsigned>> Grid::checkNeighbourhoodMatrix(bool verticalCondition, bool horizontalCondition)
{
	vector<vector<unsigned>> neighbours;
	neighbours.resize(sizeX);
	for (int i = 0; i < sizeX; i++)
	{
		neighbours[i].resize(sizeY, 0);
	}

	for (int i = 0; i < this->sizeX; i++)
	{
		for (int j = 0; j < this->sizeY; j++)
		{
			if (this->cells[i][j]->getStatus())
			{
				if (horizontalCondition && verticalCondition)
				{
					neighbours[(i - 1 + sizeX) % sizeX][(j - 1 + sizeY) % sizeY]++;
					neighbours[i][(j - 1 + sizeY) % sizeY]++;
					neighbours[(i + 1 + sizeX) % sizeX][(j - 1 + sizeY) % sizeY]++;

					neighbours[(i - 1 + sizeX) % sizeX][j]++;
					neighbours[(i + 1 + sizeX) % sizeX][j]++;

					neighbours[(i - 1 + sizeX) % sizeX][(j + 1 + sizeY) % sizeY]++;
					neighbours[i][(j + 1 + sizeY) % sizeY]++;
					neighbours[(i + 1 + sizeX) % sizeX][(j + 1 + sizeY) % sizeY]++;

				}
				else if (verticalCondition)
				{
					neighbours[(i - 1 + sizeX) % sizeX][j]++;
					neighbours[(i + 1 + sizeX) % sizeX][j]++;

					if (j - 1 >= 0)
					{
						neighbours[(i - 1 + sizeX) % sizeX][j-1]++;
						neighbours[i][j-1]++;
						neighbours[(i + 1 + sizeX) % sizeX][j-1]++;
					}
					if (j + 1 < sizeY)
					{
						neighbours[(i - 1 + sizeX) % sizeX][j + 1]++;
						neighbours[i][j + 1]++;
						neighbours[(i + 1 + sizeX) % sizeX][j + 1]++;
					}

				}
				else if (horizontalCondition)
				{
					neighbours[i][(j - 1 + sizeY) % sizeY]++;
					neighbours[i][(j + 1 + sizeY) % sizeY]++;

					if (i - 1 >= 0)
					{
						neighbours[i - 1][(j - 1 + sizeY) % sizeY]++;
						neighbours[i - 1][j]++;
						neighbours[i - 1][(j + 1 + sizeY) % sizeY]++;
					}
					if (i + 1 < sizeX)
					{
						neighbours[i + 1][(j - 1 + sizeY) % sizeY]++;
						neighbours[i + 1][j]++;
						neighbours[i + 1][(j + 1 + sizeY) % sizeY]++;
					}
				}
				else
				{
					if (i - 1 >= 0)
					{
						if (j - 1 >= 0)
						{
							neighbours[i - 1][j - 1]++;
						}
						if (j + 1 < sizeY)
						{
							neighbours[i - 1][j + 1]++;
						}
						neighbours[i - 1][j]++;
					}
					if (i + 1 < sizeX)
					{
						if (j - 1 >= 0)
						{
							neighbours[i + 1][j - 1]++;
						}
						if (j + 1 < sizeY)
						{
							neighbours[i + 1][j + 1]++;
						}
						neighbours[i + 1][j]++;
					}

					if (j - 1 >= 0)
					{
						neighbours[i][j - 1]++;
					}
					if (j + 1 < sizeY)
					{
						neighbours[i][j + 1]++;
					}
				}
			}
		}
	}
	return neighbours;
}

void Grid::calculateNextGeneration(bool verticalCondition, bool horizontalCondition)
{

	vector<vector<bool>> previous;
	previous.resize(this->cells.size());
	for (int i = 0; i < this->cells.size(); i++)
	{
		previous[i].resize(this->cells[i].size());
	}

	for (int i = 0; i < this->cells.size(); i++)
		for (int j = 0; j < this->cells[0].size(); j++)
			previous[i][j] = this->cells[i][j]->getStatus();

	for (int i = 0; i < previous.size(); i++)
	{
		for (int j = 0; j < previous[0].size(); j++)
		{
			bool isAlive = previous[i][j];
			this->previousStatus[i][j] = isAlive;							//saving status previous iteration to matrix 
			int neighbours = checkNeighbourhood(previous, i, j, verticalCondition, horizontalCondition);

			if (neighbours == 3)
				this->cells[i][j]->setStatus(1);
			else if (isAlive == true && neighbours == 2)
				this->cells[i][j]->setStatus(1);
			else
				this->cells[i][j]->setStatus(0);

			if (neighbours == 3)
			{
				this->cells[i][j]->setStatus(true);
			}
			else if (isAlive == true && neighbours == 2)
			{
				this->cells[i][j]->setStatus(true);
			}
			else
			{
				this->cells[i][j]->setStatus(false);
			}
			
		}
	}
}

void Grid::calculateNextGenerationMatrix(bool verticalCondition, bool horizontalConditiontion)
{
	vector<vector<unsigned>> neighbours;
	

	neighbours = this->checkNeighbourhoodMatrix(verticalCondition, horizontalConditiontion);

	for (int i = 0; i < sizeX; i++)
	{
		for (int j = 0; j < sizeY; j++)
		{
			if (neighbours[i][j] == 3)
				this->cells[i][j]->setStatus(1);
			else if (cells[i][j]->getStatus() == true && neighbours[i][j] == 2)
				this->cells[i][j]->setStatus(1);
			else
				this->cells[i][j]->setStatus(0);

			if (neighbours[i][j] == 3)
			{
				this->cells[i][j]->setStatus(true);
			}
			else if (cells[i][j]->getStatus() == true && neighbours[i][j] == 2)
			{
				this->cells[i][j]->setStatus(true);
			}
			else
			{
				this->cells[i][j]->setStatus(false);
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
			bool tmp = this->previousStatus[i][j];
			if (tmp != -1)
			{
				this->previousStatus[i][j] = cells[i][j]->getStatus();
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
			this->cells[j][i]->setStatus(v[i][j]);
}
