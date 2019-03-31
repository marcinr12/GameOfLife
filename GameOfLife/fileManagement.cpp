#include "fileManagement.h"

namespace fs = std::filesystem;
using namespace std;

void fileManagement::saveStateToFile(std::string encoded, std::string fileName)
{
	//opening and saving to file
	std::filesystem::path path{ fs::current_path().u8string() + "\\Saves" };	//creates folder Saves
	path /= fileName + ".rle"; //name of file
	std::filesystem::create_directories(path.parent_path());
	std::ofstream ofs(path);
	ofs << encoded;
	ofs.close();
}

std::string fileManagement::loadStateFromFile(fs::path path, int sizeX, int sizeY)
{
	// Open the stream to 'lock' the file.
	std::ifstream f{ path };

	// Obtain the size of the file.
	const auto sz = fs::file_size(path);

	// Create a buffer.
	std::string result(sz, ' ');

	// Read the whole file into the buffer.
	f.read(result.data(), sz);

	for (int i = 1; i < result.length() - 1; i++)
	{
		std::string digits = "1234567890";
		if (result[i] == 'o' || result[i] == 'b')
		{
			// if character before 'o' or 'b' is not a digit
			if (digits.find(result[i - 1]) == std::string::npos)
			{
				result.insert(i, "1");
			}
		}
		if (result[i] == '$' && digits.find(result[i - 1]) != std::string::npos)
		{
			int j = i;

			while (j > 1 && digits.find(result[j - 1]) != std::string::npos)
			{
				j--;
			}
			std::string nextLines(result, j, i - j);
			result.insert(i, std::stoi(nextLines) - 2, '$');
			result[i - 1] = '$';
		}

	}

	// if first character is 'o' or 'b' 
	if (result[0] == 'o' || result[0] == 'b')
		result.insert(0, "1");
	int lines = 0;
	for (int i = 0; i < result.length(); i++)
	{
		if (result[i] == '$')
			lines++;
	}

	std::string emptyLineNoEndSign = std::to_string(sizeY) + "b";
	for (int i = 1; i < result.length(); i++)
	{
		if (result[i - 1] == '$' && result[i] == '$')
		{
			result.insert(i, emptyLineNoEndSign);
			i += emptyLineNoEndSign.length();
		}		
	}
	
	std::string emptyLineEndSign = std::to_string(sizeY) + "b$";
	std::string emptyLines = "";
	for (int i = 0; i < sizeY - lines - 1; i++)
		emptyLines += emptyLineEndSign;

	result.erase(result.length() - 1);
	result += '$';
	result += emptyLines;

	return result;

}
