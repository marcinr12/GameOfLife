#include "MainStage.h"

unsigned int MainStage::btnCounter = 0;

MainStage::MainStage(StageParams sp)
{
	this->appWindow = std::make_shared<sf::RenderWindow>(sf::VideoMode(sp.getWindowWidth(), sp.getWindowHight() + sp.getBtnArea(), 32), "My app");
	appWindow->setFramerateLimit(60);
	appWindow->setVerticalSyncEnabled(true);
	appWindow->clear(sf::Color::Black);

}

std::shared_ptr<sf::RenderWindow> MainStage::getAppWindow()
{
	return appWindow;
}

std::map<std::string, std::shared_ptr<Button>> MainStage::getButtons()
{
	return buttons;
}

unsigned int MainStage::getBtnCounter()
{
	return btnCounter;
}

bool MainStage::isGridLoaded()
{
	return this->gridLoaded;
}

bool MainStage::isCurrentIteration()
{
	return this->currentIteration;
}

bool MainStage::isGamePaused()
{
	return this->gamePaused;
}

void MainStage::createButton(StageParams sp, sf::Font &font, std::string key, std::string text, unsigned int btnWidth, unsigned int btnHight)
{
	this->buttons[key] = std::make_shared<Button>(btnCounter * btnWidth + (btnCounter + 1) * 10, sp.getWindowHight() + (sp.getBtnArea() - btnHight) / 2, btnWidth, btnHight, &font, text);
	btnCounter++;
}

//void MainStage::initButtons(StageParams sp, sf::Font font, std::string key, std::string text, unsigned int btnWidth, unsigned int btnHight)
//{
//	this->buttons[key] = std::make_shared<Button>(10, sp.getWindowHight() + (sp.getBtnArea() - btnHight) / 2, btnWidth, btnHight, &font, text);
//	Button playBtn(10, sp.getWindowHight() + (sp.getBtnArea() - btnHight) / 2, btnWidth, btnHight, &font, text);
//}

void MainStage::eventListeners(sf::Event & event, fs::path path, Grid grid, InitialCondition ic, StageParams sp)
{
	if (buttons["LOAD_BTN"]->isPressed())
	{
		std::string decoded = fileManagement::loadStateFromFile(path, grid.getSizeX(), grid.getSizeY());
		std::vector<std::vector<bool>> v = grid.decodeGrid(decoded);
		grid.loadDecodedGrid(v);
		this->gridLoaded = true;
		this->currentIteration = true;
	}
	if (buttons["SAVE_BTN"]->isPressed())
	{
		fileManagement::saveStateToFile(grid.encodeGrid(), "abc");
	}
	if (buttons["CLEAR_BTN"]->isPressed())
	{
		grid.clearGrid();
		this->gridLoaded = false;
		this->currentIteration = true;
		buttons["STOP_BTN"]->setIdleColor(sf::Color(70, 70, 70, 200));
		buttons["PLAY_BTN"]->setIdleColor(sf::Color(70, 70, 70, 200));

	}
	if (buttons["PLAY_BTN"]->isPressed())
	{
		buttons["PLAY_BTN"]->setIdleColor(sf::Color::Red);
		buttons["STOP_BTN"]->setIdleColor(sf::Color(70, 70, 70, 200));
		this->gamePaused = false;
		this->currentIteration = true;
	}
	if (buttons["STOP_BTN"]->isPressed())
	{
		buttons["STOP_BTN"]->setIdleColor(sf::Color::Red);
		buttons["PLAY_BTN"]->setIdleColor(sf::Color(70, 70, 70, 200));
		this->gamePaused = true;
	}
	if (buttons["BACK_BTN"]->isPressed() && this->currentIteration)
	{
		grid.oneGenerationBack();
		this->currentIteration = false;
	}
	if (buttons["NEXT_BTN"]->isPressed())
	{
		grid.calculateNextGeneration(ic.getVerticalCongition(), ic.getHorizontalCondition());
		this->currentIteration = true;
	}
	sf::Mouse mouse;
	sf::Vector2f position = sf::Vector2f(mouse.getPosition(*this->getAppWindow()));
	cout << position.x << '\t' << position.y << endl;
	for (int i = 0; i < grid.getSizeX(); i++)
	{
		for (int j = 0; j < grid.getSizeY(); j++)
		{
			// checking mouse position on grid
			sf::FloatRect fr;
			fr.left = grid.getCell(i, j)->getPositionX();
			fr.top = grid.getCell(i, j)->getPositionY();
			sf::Vector2u windowSize = this->getAppWindow()->getSize();
			fr.width = sp.getWindowWidth() * 1.0 / grid.getSizeX();
			fr.height = sp.getWindowHight() * 1.0 / grid.getSizeY();
			//cout << windowSize.y << endl;

			if (fr.contains(position))
			{
				sf::RectangleShape rs;
				rs.setPosition(sf::Vector2f(fr.left, fr.top));
				rs.setSize(sf::Vector2f(fr.width, fr.height));
				rs.setFillColor(sf::Color::Blue);
				this->appWindow->draw(rs);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					while (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {}
					grid.getCell(i, j)->setStatus(!grid.getCell(i, j)->getStatus());
					this->gridLoaded = true;
				}
			}
		}
	}
	if (event.type == Event::Closed)
		appWindow->close();

}

void MainStage::renderButtons(sf::RenderWindow* target)
{
	for (auto &it : this->buttons)
	{
		it.second->render(target);
	}
}

void MainStage::updateButtons(sf::Vector2f position)
{
	for (auto &it : this->buttons)
	{
		it.second->update(position);
	}
}
