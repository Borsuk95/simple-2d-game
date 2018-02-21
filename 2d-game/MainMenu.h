#pragma once
#include "Scene.h"
#include "Button.h"

class MainMenu: public Scene
{
private:
	void onClick(Controls& control);

	enum class Options
	{
		none,
		NewGame,
		Settings,
		About,
		Exit
	};

	Options selectedOption;

protected:
	std::vector<Button> items;
	sf::Font menuFont;
public:
	MainMenu();
	~MainMenu();

	void handleEvent(Game& game) override;
	void render(Game& game) override;
	void update(Game& game) override;
	void onCreate(Game& game) override;
	void onClose(Game& game) override;
};

