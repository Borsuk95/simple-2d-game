#pragma once
#include "Entity.h"
#include <SFML/Graphics.hpp>
class Player : public Entity
{
private:
	sf::Texture texture;
	sf::Sprite ship;

public:
	Player();
	~Player();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void setPosition(const sf::Vector2f& pos) override;
	void setAngle(const float& angle) override;

	void accelerate(const sf::Vector2f& acceleration, const long long& deltaTime) override;
	void update(const long long& deltaTime) override;

	sf::Vector2f getPosition() const override;
	float getAngle() const override;
	sf::FloatRect getGlobalBound() const override;

};

