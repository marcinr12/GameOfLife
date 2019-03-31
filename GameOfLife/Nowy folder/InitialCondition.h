#pragma once
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>
#include <string>

class InitialCondition
{
	unsigned int sizeX;
	unsigned int sizeY;
	bool verticalCondition;
	bool horizontalConditon;

public:
	InitialCondition();
	InitialCondition(unsigned int, unsigned int, bool, bool);
	unsigned int getSizeX();
	unsigned int getSizeY();
	bool getVerticalCongition();
	bool getHorizontalCondition();
};
