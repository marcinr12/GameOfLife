#pragma once
#include <map>
#include <memory>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <TGUI/TGUI.hpp>

#include "fileManagement.h"
#include "Grid.h"
#include "GridInitialCondition.h"

#include "FileComboBox.h"


class MainStage
{
	bool gridLoaded = false;
	bool currentIteration = false;
	bool gamePaused = true;
	unsigned int windowWidth;
	unsigned int windowHight;

	unsigned int fpsLimit = 0;
	unsigned int printIntervalMillis = 0;


	std::shared_ptr<sf::RenderWindow> appWindow;
	std::shared_ptr<tgui::Gui> gui;
	std::map<std::string, tgui::Button::Ptr> buttons;
	std::map<std::string, tgui::Label::Ptr> labels;
	std::shared_ptr<FileComboBox> fileComboBox = NULL;
	std::shared_ptr<tgui::Slider> slider;


public:
	MainStage() = delete;
	MainStage(unsigned int x, unsigned int y);

	std::shared_ptr<sf::RenderWindow> getAppWindow();
	std::map<std::string, tgui::Widget::Ptr> getWidgets();
	tgui::Label::Ptr getLabel(string key);
	std::shared_ptr<tgui::Gui> getGui();

	unsigned getFpsLimit();
	unsigned int getPrintIntervalMillis();

	bool isGridLoaded();
	bool isCurrentIteration();
	bool isGamePaused();

	void eventListeners(sf::Event& event, Grid grid, GridInitialCondition ic);
	void loadWidgets();
};