#include "Player.h"


Player::Player():ship()
{	
	texture.loadFromFile("Resources/textures/ship.png");
	ship.setTexture(texture);
	ship.setOrigin(ship.getGlobalBounds().width / 2, ship.getGlobalBounds().height / 2);
	ship.setPosition(400, 300);
}

Player::~Player()
{
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(ship);
}

void Player::accelerate(const sf::Vector2f& acceleration, const long long& deltaTime)
{
	float delta = 1.f / 40000000.f * static_cast<float>(deltaTime);
	velocityVector += acceleration*delta;
}

void Player::update(const long long& deltaTime)
{
	ship.setTexture(texture);
	sf::Vector2f move(velocityVector.x / 1000.f * deltaTime, velocityVector.y / 1000.f * deltaTime);
	ship.move(move);
	if (rotation != 0)
	{
		ship.rotate(rotation / 1000.f * deltaTime);
		rotation = 0;
	}
}

sf::Vector2f Player::getPosition() const
{
	return ship.getPosition();
}

float Player::getAngle() const
{
	return ship.getRotation();
}


void Player::setPosition(const sf::Vector2f& pos)
{
	ship.setPosition(pos);
}

sf::FloatRect Player::getGlobalBound() const
{
	return ship.getGlobalBounds();
}

void Player::setAngle(const float& angle)
{
	ship.setRotation(angle);
}
