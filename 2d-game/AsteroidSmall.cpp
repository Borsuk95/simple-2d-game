#include "AsteroidSmall.h"



AsteroidSmall::AsteroidSmall()
{
	texture.loadFromFile("Resources/textures/asteroid_small.png");

	asteroid.setTexture(texture);

	asteroid.setOrigin(asteroid.getGlobalBounds().width / 2, asteroid.getGlobalBounds().height / 2);

	Size = AsteroidSize::Small;
}


AsteroidSmall::~AsteroidSmall()
{
}
