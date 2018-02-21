#include "Game.h"
#include "MainMenu.h"
#include "InGameScene.h"


Game::Game() :currentScene(nullptr), window(sf::VideoMode(1280, 720), "Asteroids",sf::Style::Close), event()
{
	currentScene = std::move(std::unique_ptr<Scene>(std::make_unique<MainMenu>(MainMenu())));
	currentScene->onCreate(*this);
}


Game::~Game()
{
}

void Game::changeScene(GameScene scene)
{
	currentScene->onClose(*this);
	switch (scene)
	{
	case GameScene::MenuMain:
		currentScene = std::move(std::unique_ptr<Scene>(std::make_unique<MainMenu>(MainMenu())));
		break;
	case GameScene::MenuSettings: 
		//currentScene = std::move(std::unique_ptr<Scene>(std::make_unique<SettingsMenu>(SettingsMenu())));
		break;
	case GameScene::MenuAbout: 
		//currentScene = std::move(std::unique_ptr<Scene>(std::make_unique<AboutMenu>(AboutMenu())));
		break;
	case GameScene::InGame: 
		currentScene = std::move(std::unique_ptr<Scene>(std::make_unique<InGameScene>(InGameScene())));
		break;
	case GameScene::Pause: 
		//currentScene = std::move(std::unique_ptr<Scene>(std::make_unique<PauseScene>(PauseScene())));
		break;
	case GameScene::Score: 
		//currentScene = std::move(std::unique_ptr<Scene>(std::make_unique<ScoreScene>(ScoreScene())));
		break;
	default:
		return;
	}
	currentScene->onCreate(*this);
}

void Game::handleEvent()
{
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();

		currentScene->handleEvent(*this);   
	}
}

void Game::render()
{
	window.clear();
	currentScene->render(*this);
	window.display();
}

void Game::update()
{
	currentScene->update(*this);
}

bool Game::isOpen() const noexcept
{
	return window.isOpen();
}