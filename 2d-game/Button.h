#pragma once
#include "Controls.h"

class Button: public Controls
{
protected:
	//virtual void onHover() override;
	//virtual void onClick() override;
	//virtual void onLeft() override;
	void checkAlignment(Controls& control);
public:
	Button(std::string str, sf::Font& font, unsigned int size = 30);
	~Button() override = default;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	virtual void eventhandler(sf::Event& event, sf::RenderWindow& window) override;
	virtual void setPosition(const float& x, const float& y) override;
	virtual void setPosition(const sf::Vector2f& pos) override;
	//virtual void setFont(const sf::Font& font) override;
	//virtual void setOnHover(std::function<void(Controls&)> operation) override;
	//virtual void setOnClick(std::function<void(Controls&)> operation) override;
	//virtual void setOnLeft(std::function<void(Controls&)> operation) override;
	virtual void alignToTop(Controls& control, sf::Vector2f offset = sf::Vector2f()) override;
	virtual void alignToBottom(Controls& control, sf::Vector2f offset = sf::Vector2f()) override;
	virtual void alignToLeft(Controls& control, sf::Vector2f offset = sf::Vector2f()) override;
	virtual void alignToRight(Controls& control, sf::Vector2f offset = sf::Vector2f()) override;
	//virtual void setText(std::string str) override;
	virtual sf::Vector2f getPosition() const override;
	virtual sf::FloatRect getGlobalBounds() const override;
	virtual sf::Vector2f getCenter() const override;
	//virtual const sf::Font* getFont() const override;
	virtual void update() override;
};
