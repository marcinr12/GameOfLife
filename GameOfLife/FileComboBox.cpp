#include "FileComboBox.h"


FileComboBox::FileComboBox(tgui::ComboBox::Ptr fileComboBox)
{
	this->fileComboBox = fileComboBox;
}


FileComboBox::~FileComboBox()
{
}

std::shared_ptr<tgui::ComboBox>& FileComboBox::getFileComboBoxPtr()
{
	return fileComboBox;
}

std::vector<std::filesystem::path>& FileComboBox::getPaths()
{
	return paths;
}

std::filesystem::path FileComboBox::getPath(unsigned index)
{
	return paths[index];
}

void FileComboBox::addFiles()
{
	// path to directory";
	std::string path = "Patterns";
	for (const auto& entry : std::filesystem::directory_iterator(path))
	{
		fileComboBox->addItem(entry.path().filename().generic_string());
		paths.push_back(entry.path());
	}
}

int FileComboBox::getSelectedIndex()
{
	return this->selectedIndex;
}


bool FileComboBox::isChanged()
{
	if (selectedIndex != fileComboBox->getSelectedItemIndex())
	{
		selectedIndex = fileComboBox->getSelectedItemIndex();
		return true;
	}
	return false;
}

