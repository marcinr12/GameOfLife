#pragma once

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <sstream>

#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

#include <iostream>

enum button_state { BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE };

class Button
{

public:

	short unsigned buttonState;

	sf::RectangleShape shape;
	sf::Font* font;
	sf::Text text;

	sf::Color idleColor;
	sf::Color hoverColor;
	sf::Color activeColor;

public:
	Button() = delete;
	Button(float x, float y, float width, float height, sf::Font* font, std::string text, sf::Color idleColor = sf::Color(70, 70, 70, 200), sf::Color hoverColor = sf::Color(150, 150, 150, 255), sf::Color activeColor = sf::Color(20, 20, 20, 200));
	~Button();


	bool isPressed();

	void setIdleColor(sf::Color idleColor);

	void update(const sf::Vector2f mousePos);
	void render(sf::RenderTarget* target);
};

