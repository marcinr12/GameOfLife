#include "Cell.h"

int Cell::cellNumber = 0;

Cell::Cell()
{
	this->ID = cellNumber;
	this->cellNumber++;
	this->positionX = 0;
	this->status = false;
}

Cell::Cell(const Cell & cell)
{
	this->ID = cellNumber;
	this->cellNumber++;
	this->positionX = cell.positionX;
	this->positionY = cell.positionY;
	this->status = cell.status;
}

Cell::Cell(unsigned int x, unsigned int y, bool status)
{
	this->ID = cellNumber;
	this->cellNumber++;
	this->positionX = x;
	this->positionY = y;
	this->status = status;
}


void Cell::setPositionX(unsigned int x)
{
	this->positionX = x;
}

void Cell::setPositionY(unsigned int y)
{
	this->positionY = y;
}

void Cell::setStatus(bool status)
{
	this->status = status;
}

unsigned int Cell::getID()
{
	return this->ID;
}

unsigned int Cell::getPositionX()
{
	return this->positionX;
}

unsigned int Cell::getPositionY()
{
	return this->positionY;
}

bool Cell::getStatus()
{
	return this->status;
}

