#include "Entity.h"



Entity::Entity() noexcept:rotation(0),velocityVector(0,0)
{
}


Entity::~Entity()
{
}

void Entity::setRotation(const float& rot) noexcept
{
	rotation = rot;
}

void Entity::setVelocity(const sf::Vector2f& velocity) noexcept
{
	velocityVector = velocity;
}

float Entity::getRotation() const noexcept
{
	return rotation;
}

sf::Vector2f Entity::getVelocity() const noexcept
{
	return velocityVector;
}
