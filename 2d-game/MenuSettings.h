#pragma once
#include "MainMenu.h"

class MenuSettings:public MainMenu
{
	void onClick(Controls& control);

public:
	MenuSettings();
	~MenuSettings();

	void onCreate(Game& game) override;
	void onClose(Game& game) override;
	void update(Game& game) override;
};

