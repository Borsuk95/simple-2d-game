#include "Game.h"



int main()
{
	Game game;

	game.window.setVerticalSyncEnabled(true);

	while (game.isOpen())
	{
		auto start = game.timer.now();

		game.handleEvent();
		game.update();
		game.render();

		auto stop = game.timer.now();

		game.deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
	}
	return 0;
}
