#include "MainStage.h"

MainStage::MainStage(unsigned int x, unsigned int y)
{
	this->windowWidth = x;
	this->windowHight = y;
	this->appWindow = std::make_shared<sf::RenderWindow>(sf::VideoMode(x, y, 32), "Game of Life");
	this->gui = std::make_shared<tgui::Gui>(*this->appWindow);


	this->appWindow->setSize(sf::Vector2u(x, y));
	this->appWindow->clear(sf::Color::Black);
	loadWidgets();
}

std::shared_ptr<sf::RenderWindow> MainStage::getAppWindow()
{
	return this->appWindow;
}


tgui::Label::Ptr MainStage::getLabel(string key)
{
	return this->labels[key];
}

std::shared_ptr<tgui::Gui> MainStage::getGui()
{
	return this->gui;
}

unsigned MainStage::getFpsLimit()
{
	return this->fpsLimit;
}

unsigned int MainStage::getPrintIntervalMillis()
{
	return this->printIntervalMillis;
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



void MainStage::eventListeners(sf::Event & event, Grid grid, GridInitialCondition ic)
{
	int dt = 50;
	if (buttons["LOAD_BTN"]->mouseOnWidget(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
	{

		int index = fileComboBox->getFileComboBoxPtr()->getSelectedItemIndex();
		if (index < 0)
			return;
		grid.clearGrid();
		fs::path filePath = fileComboBox->getPath(index);
		std::string decoded = fileManagement::loadStateFromFile(filePath, grid.getSizeX(), grid.getSizeY());
		std::vector<std::vector<bool>> v = grid.decodeGrid(decoded);
		grid.loadDecodedGrid(v);


		this->gridLoaded = true;
		this->currentIteration = true;
		sleep(sf::milliseconds(dt));
	}

	if (buttons["SAVE_BTN"]->mouseOnWidget(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
	{
		fileManagement::saveStateToFile(grid.encodeGrid(), "MySave");
		sleep(sf::milliseconds(dt));
	}
	if (buttons["CLEAR_BTN"]->mouseOnWidget(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
	{
		grid.clearGrid();
		this->gridLoaded = false;
		this->currentIteration = true;
		//buttons["STOP_BTN"]->setIdleColor(sf::Color(70, 70, 70, 200));
		//buttons["PLAY_BTN"]->setIdleColor(sf::Color(70, 70, 70, 200));
		sleep(sf::milliseconds(dt));

	}
	if (buttons["PLAY_BTN"]->mouseOnWidget(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
	{
		//buttons["PLAY_BTN"]->setIdleColor(sf::Color::Red);
		//buttons["STOP_BTN"]->setIdleColor(sf::Color(70, 70, 70, 200));
		this->gamePaused = false;
		this->currentIteration = true;
		sleep(sf::milliseconds(dt));

	}
	if (buttons["STOP_BTN"]->mouseOnWidget(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
	{
		//buttons["STOP_BTN"]->setIdleColor(sf::Color::Red);
		//buttons["PLAY_BTN"]->setIdleColor(sf::Color(70, 70, 70, 200));
		this->gamePaused = true;
		sleep(sf::milliseconds(dt));
	}
	if (buttons["BACK_BTN"]->mouseOnWidget(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)) && this->currentIteration)
	{
		grid.oneGenerationBack();
		this->currentIteration = false;
	}
	if (buttons["NEXT_BTN"]->mouseOnWidget(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
	{
		grid.calculateNextGeneration(ic.getVerticalCongition(), ic.getHorizontalCondition());
		this->currentIteration = true;
		sleep(sf::milliseconds(dt));
	}
	if (fpsLimit != slider->getValue())
	{
		fpsLimit = slider->getValue();
		appWindow->setFramerateLimit(fpsLimit);
		printIntervalMillis = static_cast<unsigned int>((1.0 / fpsLimit) * 1000);
		labels["setFpsLimit"]->setText(to_string(fpsLimit));
	}

	sf::Mouse mouse;
	sf::Vector2f position = sf::Vector2f(mouse.getPosition(*this->getAppWindow()));
	for (unsigned i = 0; i < grid.getSizeX(); i++)
	{
		for (unsigned j = 0; j < grid.getSizeY(); j++)
		{
			// checking mouse position on grid
			sf::FloatRect fr;
			fr.left = grid.getCell(i, j)->getPositionX();
			fr.top = grid.getCell(i, j)->getPositionY();
			sf::Vector2u windowSize = this->getAppWindow()->getSize();
			fr.width = static_cast<int>(windowWidth * 1.0 / grid.getSizeX());
			fr.height = static_cast<int>(windowHight * 1.0 / grid.getSizeY());

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

void MainStage::loadWidgets()
{
	this->gui->loadWidgetsFromFile("./form.txt");
	
	std::vector<tgui::Widget::Ptr> w = gui->getWidgets();

	for (int i = 0; i < w.size(); i++)
	{
		string name = gui->getWidgetName(w[i]);
		string type = w[i]->getWidgetType();
		
		if (type == "Button")
			buttons[name] = w[i]->cast<tgui::Button>();
		else if (type == "Label")
		{
			labels[name] = w[i]->cast<tgui::Label>();
		}
		else if (type == "ComboBox")
		{
			this->fileComboBox = std::make_shared<FileComboBox>(w[i]->cast<tgui::ComboBox>());
			this->fileComboBox->addFiles();
		}
		else if (type == "Slider")
		{
			slider = w[i]->cast<tgui::Slider>();
		}
		else
			cout << "Unsaved widget!!!\t" << type << '\t' << name << endl;
	}		
}


