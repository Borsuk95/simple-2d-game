#pragma once
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <functional>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>


class Controls : public sf::Drawable
{

protected:
	enum class State
	{
		normal,
		hovered,
		pressed,
		released
	};

	enum class Alignment
	{
		none,
		top,
		bottom,
		left,
		right
	};

	sf::Text text;

	Controls* alignedTo;

	Controls* topAlignedControl;
	Controls* bottomAlignedControl;
	Controls* leftAlignedControl;
	Controls* rightAlignedControl;

	std::function<void(Controls&)> onHoverOperation;
	std::function<void(Controls&)> onClickOperation;
	std::function<void(Controls&)> onLeftOperation;

	sf::Color normalColor;
	sf::Color hoverColor;
	sf::Color clickColor;

	State currentState;

	Alignment alignmentType;

	sf::Vector2f offset;

	virtual void onHover();
	virtual void onClick();
	virtual void onLeft();
	virtual bool isHover(sf::RenderWindow& window) const;

public:

	Controls(std::string str, sf::Font& font, unsigned int Size = 30);
	virtual ~Controls() = default;

	const Controls& getReference() const noexcept;

	void setNormalColor(sf::Color color) noexcept;
	void setHoverColor(sf::Color color) noexcept;
	void setClickColor(sf::Color color) noexcept;
	void alignFree() noexcept;

	virtual void eventhandler(sf::Event& event, sf::RenderWindow& window) = 0;

	virtual void setPosition(const float& x, const float& y) = 0;
	virtual void setPosition(const sf::Vector2f& pos) = 0;

	virtual void setFont(const sf::Font& font);

	virtual void setOnHover(std::function<void(Controls&)> operation);
	virtual void setOnClick(std::function<void(Controls&)> operation);
	virtual void setOnLeft(std::function<void(Controls&)> operation);

	virtual void alignToTop(Controls& control, sf::Vector2f offset = sf::Vector2f()) = 0;
	virtual void alignToBottom(Controls& control, sf::Vector2f offset = sf::Vector2f()) = 0;
	virtual void alignToLeft(Controls& control, sf::Vector2f offset = sf::Vector2f()) = 0;
	virtual void alignToRight(Controls& control, sf::Vector2f offset = sf::Vector2f()) = 0;

	virtual void setText(std::string str);

	virtual sf::Vector2f getPosition() const = 0;
	virtual sf::FloatRect getGlobalBounds() const = 0;
	virtual const sf::Font* getFont() const;
	virtual sf::Vector2f getCenter() const = 0;
	virtual std::string getText() const;

	sf::Vector2f getOffset() const;

	virtual void update() = 0;

	friend class Button;
};
