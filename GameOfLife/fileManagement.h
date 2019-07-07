#pragma once
#include <vector>
#include <string>
#include <filesystem>
#include <fstream>
#include <iostream>


namespace fs = std::filesystem;

namespace fileManagement
{
	void saveStateToFile(std::string, std::string);
	std::string loadStateFromFile(fs::path path, int, int);
}