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
	return this->fileComboBox;
}

std::vector<std::filesystem::path>& FileComboBox::getPaths()
{
	return this->paths;
}

std::filesystem::path FileComboBox::getPath(unsigned index)
{
	return this->paths[index];
}

void FileComboBox::addFiles()
{

	for (const auto& entry : std::filesystem::directory_iterator(path))
	{
		this->fileComboBox->addItem(entry.path().filename().generic_string());
		this->paths.push_back(entry.path());
	}
}

int FileComboBox::getSelectedIndex()
{
	return this->selectedIndex;
}


bool FileComboBox::isChanged()
{
	if (this->selectedIndex != this->fileComboBox->getSelectedItemIndex())
	{
		this->selectedIndex = this->fileComboBox->getSelectedItemIndex();
		return true;
	}
	return false;
}

