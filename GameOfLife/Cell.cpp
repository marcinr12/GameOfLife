#include "Cell.h"

int Cell::cellNumber = 0;

Cell::Cell()
{
	ID = cellNumber;
	cellNumber++;
}

Cell::Cell(unsigned int x, unsigned int y)
{
	ID = cellNumber;
	cellNumber++;
	possisionX = x;
	possisionY = y;
}

void Cell::setPossisionX(unsigned int x)
{
	possisionX = x;
}

void Cell::setPossisionY(unsigned int y)
{
	possisionY = y;
}

void Cell::setStatus(bool status)
{
	this->status = status;
}

unsigned int Cell::getID()
{
	return ID;
}

unsigned int Cell::getPossisionX()
{
	return possisionX;
}

unsigned int Cell::getPossisionY()
{
	return possisionY;
}

bool Cell::getStatus()
{
	return status;
}

