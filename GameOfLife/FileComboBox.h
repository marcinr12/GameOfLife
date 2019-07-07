#pragma once
#include <TGUI/Widgets/ComboBox.hpp>
#include <string>
#include <filesystem>
#include <vector>

class FileComboBox
{
	// path to directory";
	std::string path = "Patterns";

	tgui::ComboBox::Ptr fileComboBox;
	std::vector<std::filesystem::path> paths;
	int selectedIndex = -1;


public:
	FileComboBox() = delete;
	FileComboBox(tgui::ComboBox::Ptr fileComboBox);
	~FileComboBox();

	std::shared_ptr<tgui::ComboBox>& getFileComboBoxPtr();
	std::vector<std::filesystem::path>& getPaths();
	std::filesystem::path getPath(unsigned index);
	void addFiles();
	int getSelectedIndex();
	bool isChanged();

};

