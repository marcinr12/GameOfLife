#include "InitialCondition.h"

InitialCondition::InitialCondition()
{
	boost::property_tree::ptree tree;
	boost::property_tree::read_json("InitialCondition.json", tree);
	this->sizeX = tree.get<unsigned int>("sizeX");
	this->sizeY = tree.get<unsigned int>("sizeY");
	this->verticalCondition = tree.get<bool>("verticalCondition");
	this->horizontalConditon = tree.get<bool>("horizontalCondition");
}

InitialCondition::InitialCondition(unsigned int x, unsigned int y, bool verticalCondition, bool horizontalCondition)
{
	this->sizeX = x;
	this->sizeY = y;
	this->verticalCondition = verticalCondition;
	this->horizontalConditon = horizontalCondition;
}

unsigned int InitialCondition::getSizeX()
{
	return sizeX;
}

unsigned int InitialCondition::getSizeY()
{
	return sizeY;
}

bool InitialCondition::getVerticalCongition()
{
	return this->verticalCondition;
}

bool InitialCondition::getHorizontalCondition()
{
	return this->horizontalConditon;
}
