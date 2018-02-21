#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Drawable.hpp>

class Entity: public sf::Drawable
{
protected:
	float rotation;
	sf::Vector2f velocityVector;
public:
	Entity() noexcept;
	virtual ~Entity();

	void setRotation(const float& rot) noexcept;
	virtual void setPosition(const sf::Vector2f& pos) = 0;
	virtual void setAngle(const float& angle) = 0;
	void setVelocity(const sf::Vector2f& velocity) noexcept;

	virtual void accelerate(const sf::Vector2f& acceleration, const long long& deltaTime) = 0;
	virtual void update(const long long& deltaTime) = 0;

	float getRotation() const noexcept;
	virtual sf::Vector2f getPosition() const = 0;
	sf::Vector2f getVelocity() const noexcept;
	virtual float getAngle() const = 0;
	virtual sf::FloatRect getGlobalBound() const = 0;

};

