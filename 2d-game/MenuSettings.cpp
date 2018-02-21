#include "MenuSettings.h"
#include "Game.h"


void MenuSettings::onClick(Controls& control)
{
}

MenuSettings::MenuSettings()
{
}


MenuSettings::~MenuSettings()
{
}

void MenuSettings::onCreate(Game& game)
{
	menuFont.loadFromFile("Resources/font/Gameplay.ttf");

	std::function<void(Controls&)> onClickOperation = [&](Controls& control)
	{
		this->onClick(control);
	};

	auto windowDimension = game.window.getSize();
	sf::Vector2f offset(0, 20);

	items.reserve(4);

	items.push_back(Button("New Game", menuFont));
	items[0].setHoverColor(sf::Color::Green);
	items[0].setClickColor(sf::Color::Red);
	items[0].setOnClick(onClickOperation);

	items.push_back(Button("Settings", menuFont));
	items[1].alignToBottom(items[0], offset);
	items[1].setHoverColor(sf::Color::Green);
	items[1].setClickColor(sf::Color::Red);
	items[1].setOnClick(onClickOperation);

	items.push_back(Button("About", menuFont));
	items[2].alignToBottom(items[1], offset);
	items[2].setHoverColor(sf::Color::Green);
	items[2].setClickColor(sf::Color::Red);
	items[2].setOnClick(onClickOperation);

	items.push_back(Button("Exit", menuFont));
	items[3].alignToBottom(items[2], offset);
	items[3].setHoverColor(sf::Color::Green);
	items[3].setClickColor(sf::Color::Red);
	items[3].setOnClick(onClickOperation);

	auto textDimension = items[0].getGlobalBounds();
	items[0].setPosition(windowDimension.x / 2 - textDimension.width / 2,
		windowDimension.y / 2 - textDimension.height*items.size() / 2);
}

void MenuSettings::onClose(Game& game)
{
}

void MenuSettings::update(Game& game)
{
}
