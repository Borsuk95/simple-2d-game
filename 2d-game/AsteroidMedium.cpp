#include "AsteroidMedium.h"



AsteroidMedium::AsteroidMedium()
{
	texture.loadFromFile("Resources/textures/asteroid_medium.png");

	asteroid.setTexture(texture);

	asteroid.setOrigin(asteroid.getGlobalBounds().width / 2, asteroid.getGlobalBounds().height / 2);

	Size = AsteroidSize::Medium;
}


AsteroidMedium::~AsteroidMedium()
{
}
