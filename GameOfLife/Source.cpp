#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <chrono>
#include "Cell.h"
#include "Grid.h"
#include "GridInitialCondition.h"
#include "fileManagement.h"
#include "MainStage.h"


using namespace std;
using namespace sf;

int main()
{
	//InitialCondition ic;
	//GridInitialCondition ic;
	GridInitialCondition ic(100, 100, false, false);

	MainStage ms(800, 600);
	Grid grid(ic.getSizeX(), ic.getSizeY(), 600, 600);
	sf::Mouse mouse;
	sf::Font arialFont;
	sf::Clock clock;
	sf::Event event;
	sf::Clock clockFps;


	if (!arialFont.loadFromFile("arial.ttf"))
	{
		cout << "ERROR WITH LOADING FONT" << endl;
	}	
	
	bool isNextGenerationCalculated = false;
	bool paused = true;
	bool loaded = false;
	bool isThisNow = true;
	unsigned fileComboBoxPrevIndex = -1;


	while (ms.getAppWindow()->isOpen())
	{

		sf::Vector2f position = sf::Vector2f(mouse.getPosition(*ms.getAppWindow()));
		sf::Event event;
		while (ms.getAppWindow()->pollEvent(event))
		{
			ms.eventListeners(event, grid, ic);
			ms.getGui()->handleEvent(event);
		}

		int time = clock.getElapsedTime().asMilliseconds();

		if (isNextGenerationCalculated == false && !ms.isGamePaused() && ms.isGridLoaded())
		{
			//grid.calculateNextGeneration(ic.getVerticalCongition(), ic.getHorizontalCondition());
			grid.calculateNextGenerationMatrix(ic.getVerticalCongition(), ic.getHorizontalCondition());
			isNextGenerationCalculated = true;
		}

		ms.getAppWindow()->clear();
		ms.getGui()->draw();

		//printing grid
		grid.printGridSFML(*ms.getAppWindow());
		ms.getAppWindow()->display();

		isNextGenerationCalculated = false;
		clock.restart();	

		ms.getLabel("displayedFps")->setText(std::to_string((int)(1.0 / clockFps.restart().asSeconds())));
	}


	return 0;
}