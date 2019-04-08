#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <chrono>
#include "Cell.h"
#include "Grid.h"
#include "InitialCondition.h"
#include "fileManagement.h"
#include "Button.h"
#include "StageParams.h"
#include "MainStage.h"

// TO DO 
// #include <ncurses.h>

// README
// WASD navigation
// G change status of blinking cell
// V start game
// P pause / start
// -> F save to file
// -> L load from file
// -> C clear grid


using namespace std;
using namespace sf;

int main()
{
	//InitialCondition ic;
	InitialCondition ic(50, 50, true, false);
	StageParams sp(800, 800, 60, 100);
	MainStage ms(sp);
	Grid grid(ic.getSizeX(), ic.getSizeY(), sp.getWindowHight(), sp.getWindowWidth());
	fs::path path{ fs::current_path().u8string() + "\\Saves\\abc" + ".rle" };
	sf::Mouse mouse;
	sf::Font arialFont;
	sf::Clock clock;
	sf::Event event;


	if (!arialFont.loadFromFile("arial.ttf"))
	{
		cout << "ERROR WITH LOADING FONT" << endl;
	}	
		
	unsigned int btnWide = 40;
	unsigned int btnHigh = 30;

	int btnWidth = (sp.getWindowHight() - 7 * 10) / 7 - 1;

	ms.createButton(sp, arialFont, "LOAD_BTN", "LOAD", btnWidth, 30);
	ms.createButton(sp, arialFont, "SAVE_BTN", "SAVE", btnWidth, 30);
	ms.createButton(sp, arialFont, "CLEAR_BTN", "CLEAR", btnWidth, 30);
	ms.createButton(sp, arialFont, "PLAY_BTN", "PLAY", btnWidth, 30);
	ms.createButton(sp, arialFont, "STOP_BTN", "STOP", btnWidth, 30);
	ms.createButton(sp, arialFont, "BACK_BTN", "BACK", btnWidth, 30);
	ms.createButton(sp, arialFont, "NEXT_BTN", "NEXT", btnWidth, 30);

	
	bool isNextGenerationCalculated = false;
	bool paused = true;
	bool loaded = false;
	bool isThisNow = true;

	while (ms.getAppWindow()->isOpen())
	{
		//printing grid
		grid.printGridSFML(*ms.getAppWindow(), sp.getWindowWidth(), sp.getWindowHight());

		sf::Vector2f position = sf::Vector2f(mouse.getPosition(*ms.getAppWindow()));
		// event listener
		while (ms.getAppWindow()->pollEvent(event))
		{
			ms.eventListeners(event, path, grid, ic, sp);
		}
		
		
		int time = clock.getElapsedTime().asMilliseconds();

		//if time elapsed 
		if (time >= sp.getPrintIntervalMillis())
		{
			ms.updateButtons(position);
			ms.renderButtons(ms.getAppWindow().get());
			ms.getAppWindow()->display();

			isNextGenerationCalculated = false;
			clock.restart();
		}
		//sleep and calculate otherwise
		else
		{	
			if (isNextGenerationCalculated == false && !ms.isGamePaused() && ms.isGridLoaded())
			{ 
				grid.calculateNextGeneration(ic.getVerticalCongition(), ic.getHorizontalCondition());
				isNextGenerationCalculated = true;
			}
			sleep(sf::milliseconds(sp.getPrintIntervalMillis() - time));
		}
	}

	return 0;
}