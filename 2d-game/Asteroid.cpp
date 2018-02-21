#include "Asteroid.h"



Asteroid::Asteroid()
{

}


Asteroid::~Asteroid()
{
}

void Asteroid::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(asteroid);
}

void Asteroid::setPosition(const sf::Vector2f& pos)
{
	asteroid.setPosition(pos);
}

void Asteroid::setAngle(const float& angle)
{
	asteroid.setRotation(angle);
}

void Asteroid::accelerate(const sf::Vector2f& acceleration, const long long& deltaTime)
{
}

void Asteroid::update(const long long& deltaTime)
{
	asteroid.setTexture(texture);
	sf::Vector2f move(velocityVector.x / 1000.f * deltaTime, velocityVector.y / 1000.f * deltaTime);
	asteroid.move(move);
	asteroid.rotate(rotation / 1000 * deltaTime);
}

sf::Vector2f Asteroid::getPosition() const
{
	return asteroid.getPosition();
}

float Asteroid::getAngle() const
{
	return asteroid.getRotation();
}

sf::FloatRect Asteroid::getGlobalBound() const
{
	return asteroid.getGlobalBounds();
}