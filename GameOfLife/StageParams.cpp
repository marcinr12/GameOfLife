#include "StageParams.h"


StageParams::StageParams(unsigned int windowWidth, unsigned int windowHight, unsigned int btnArea, unsigned int printIntervalMillis)
{
	this->windowWidth = windowWidth;
	this->windowHight = windowHight;
	this->btnArea = btnArea;
	this->printIntervalMillis = printIntervalMillis;
}

StageParams::~StageParams()
{
}

unsigned int StageParams::getWindowWidth()
{
	return this->windowWidth;
}

unsigned int StageParams::getWindowHight()
{
	return this->windowHight;
}

unsigned int StageParams::getBtnArea()
{
	return this->btnArea;
}

unsigned int StageParams::getPrintIntervalMillis()
{
	return this->printIntervalMillis;
}

void StageParams::setWindowWidth(unsigned int windowWidth)
{
	this->windowWidth = windowWidth;
}

void StageParams::setWindowHight(unsigned int windowHight)
{
	this->windowHight = windowHight;
}

void StageParams::setBtnArea(unsigned int btnArea)
{
	this->btnArea = btnArea;
}

void StageParams::setPrintIntervalMillis(unsigned int printIntervalMillis)
{
	this->printIntervalMillis = printIntervalMillis;
}
