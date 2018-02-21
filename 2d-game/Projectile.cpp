#include "Projectile.h"



Projectile::Projectile()
{
	texture.loadFromFile("Resources/textures/projectile.png");

	asteroid.setTexture(texture);

	asteroid.setOrigin(asteroid.getGlobalBounds().width / 2, asteroid.getGlobalBounds().height / 2);
}


Projectile::~Projectile()
{
}
