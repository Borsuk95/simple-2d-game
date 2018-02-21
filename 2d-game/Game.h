#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include "Scene.h"
#include <memory>
#include <chrono>


class Game final
{
private:
	std::unique_ptr<Scene> currentScene;

public:
	enum class GameScene
	{
		MenuMain,
		MenuSettings,
		MenuAbout,
		InGame,
		Pause,
		Score
	};

	sf::RenderWindow window;
	sf::Event event;
	std::chrono::high_resolution_clock timer;
	long long deltaTime;

	Game();
	~Game();

	void changeScene(GameScene scene);
	void handleEvent();
	void render();
	void update();
	bool isOpen() const noexcept;
};
