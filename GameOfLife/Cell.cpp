#include "Cell.h"

int Cell::cellNumber = 0;

Cell::Cell()
{
	ID = cellNumber;
	cellNumber++;
}

Cell::Cell(const Cell & cell)
{
	ID = cellNumber;
	cellNumber++;
	this->positionX = cell.positionX;
	this->positionY = cell.positionY;
	this->status = cell.status;
}

Cell::Cell(unsigned int x, unsigned int y, bool status)
{
	ID = cellNumber;
	cellNumber++;
	positionX = x;
	positionY = y;
	this->status = status;
}


void Cell::setPositionX(unsigned int x)
{
	positionX = x;
}

void Cell::setPositionY(unsigned int y)
{
	positionY = y;
}

void Cell::setStatus(bool status)
{
	this->status = status;
}

unsigned int Cell::getID()
{
	return ID;
}

unsigned int Cell::getPositionX()
{
	return positionX;
}

unsigned int Cell::getPositionY()
{
	return positionY;
}

bool Cell::getStatus()
{
	return status;
}

