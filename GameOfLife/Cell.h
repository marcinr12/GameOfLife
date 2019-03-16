#pragma once
#include <Windows.h>

class Cell
{
	static int cellNumber;
	unsigned int possisionX;
	unsigned int possisionY;
	unsigned int ID;
	bool status;

public:
	Cell();
	Cell(unsigned int, unsigned int);

	void setPossisionX(unsigned int);
	void setPossisionY(unsigned int);
	void setStatus(bool);
	
	unsigned int getID();
	unsigned int getPossisionX();
	unsigned int getPossisionY();
	bool getStatus();

};