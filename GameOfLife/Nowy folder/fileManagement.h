#pragma once
#include <vector>
#include <string>
#include "Grid.h"

namespace fileManagement
{
	vector<string> encode(Grid g);
	void saveStateToFile(Grid g);
}