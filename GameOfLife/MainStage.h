#pragma once
#include "StageParams.h"
#include "Button.h"
#include <map>
#include <memory>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "fileManagement.h"
#include "Grid.h"
#include "InitialCondition.h"


class MainStage
{
	bool gridLoaded = false;
	bool currentIteration = false;
	bool gamePaused = true;


	static unsigned int btnCounter;
	std::shared_ptr<sf::RenderWindow> appWindow;
	std::map<std::string, std::shared_ptr<Button>> buttons;


public:
	MainStage() = delete;
	MainStage(StageParams sp);

	std::shared_ptr<sf::RenderWindow> getAppWindow();
	std::map<std::string, std::shared_ptr<Button>> getButtons();
	unsigned int getBtnCounter();
	bool isGridLoaded();
	bool isCurrentIteration();
	bool isGamePaused();

	void createButton(StageParams sp, sf::Font &font, std::string key, std::string text = "BUTTON", unsigned int btnWidth = 40, unsigned int btnHight = 30);
	void initButtons(StageParams sp, sf::Font font, std::string key, std::string text = "BUTTON", unsigned int btnWidth = 40, unsigned int btnHight = 30);


	//void renderButtons(sf::RenderTarget* target = NULL);
	void eventListeners(sf::Event& event, fs::path path, Grid grid, InitialCondition ic, StageParams sp);
	void renderButtons(sf::RenderWindow* target);
	void updateButtons(sf::Vector2f position);
};