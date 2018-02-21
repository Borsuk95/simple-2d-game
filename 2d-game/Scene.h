#pragma once

class Game;

class Scene
{
public:
	Scene();
	virtual ~Scene();

	virtual void handleEvent(Game& game) = 0;
	virtual void render(Game& game) = 0;
	virtual void update(Game& game) = 0;
	virtual void onCreate(Game& game) = 0;
	virtual void onClose(Game& game) = 0;

};

