#include "AsteroidBig.h"



AsteroidBig::AsteroidBig()
{
	texture.loadFromFile("Resources/textures/asteroid_big.png");

	asteroid.setTexture(texture);

	asteroid.setOrigin(asteroid.getGlobalBounds().width / 2, asteroid.getGlobalBounds().height / 2);

	Size = AsteroidSize::Big;
}


AsteroidBig::~AsteroidBig()
{
}
