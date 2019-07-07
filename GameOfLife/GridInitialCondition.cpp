#include "GridInitialCondition.h"

GridInitialCondition::GridInitialCondition()
{
	boost::property_tree::ptree tree;
	boost::property_tree::read_json("InitialCondition.json", tree);

	this->sizeX = tree.get<unsigned int>("sizeX");
	this->sizeY = tree.get<unsigned int>("sizeY");
	this->verticalCondition = tree.get<bool>("verticalCondition");
	this->horizontalConditon = tree.get<bool>("horizontalCondition");
}

GridInitialCondition::GridInitialCondition(unsigned int sizeX, unsigned int sizeY, bool verticalCondition, bool horizontalCondition)
{
	this->sizeX = sizeX;
	this->sizeY = sizeY;
	this->verticalCondition = verticalCondition;
	this->horizontalConditon = horizontalCondition;
}

unsigned int GridInitialCondition::getSizeX()
{
	return this->sizeX;
}

unsigned int GridInitialCondition::getSizeY()
{
	return this->sizeY;
}

bool GridInitialCondition::getVerticalCongition()
{
	return this->verticalCondition;
}

bool GridInitialCondition::getHorizontalCondition()
{
	return this->horizontalConditon;
}
