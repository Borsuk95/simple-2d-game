#include "MainMenu.h"
#include "Game.h"


void MainMenu::onClick(Controls& control)
{
	auto buttonText(control.getText());

	if (buttonText == "New Game")
	{
		selectedOption = Options::NewGame;
	}
	else if (buttonText == "Settings")
	{
		selectedOption = Options::Settings;
	}
	else if (buttonText == "About")
	{
		selectedOption = Options::About;
	}
	else if (buttonText == "Exit")
	{
		selectedOption = Options::Exit;
	}
}

MainMenu::MainMenu() :selectedOption(Options::none), items(), menuFont()
{
}


MainMenu::~MainMenu()
{
}

void MainMenu::handleEvent(Game& game)
{
	for (auto& element : items)
	{
		element.eventhandler(game.event, game.window);
	}
}

void MainMenu::render(Game& game)
{
	for (auto& element : items)
	{
		game.window.draw(element);
	}
}

void MainMenu::update(Game& game)
{
	switch (selectedOption)
	{
	case Options::none:
		
		break;
	case Options::NewGame:
		game.changeScene(Game::GameScene::InGame);
		break;
	case Options::Settings:
		//game.changeScene(Game::GameScene::MenuSettings);
		break;
	case Options::About: break;
	case Options::Exit:
		game.window.close();
		break;
	default: ;
	}
}

void MainMenu::onCreate(Game& game)
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

void MainMenu::onClose(Game& game)
{
}