#pragma once
#include <Windows.h>

class Cell
{
	static int cellNumber;
	unsigned int positionX;
	unsigned int positionY;
	unsigned int ID;
	bool status;

public:
	Cell();
	Cell(const Cell &cell);
	Cell(unsigned int x, unsigned int y, bool status);

	void setPositionX(unsigned int);
	void setPositionY(unsigned int);
	void setStatus(bool);
	
	unsigned int getID();
	unsigned int getPositionX();
	unsigned int getPositionY();
	bool getStatus();
};