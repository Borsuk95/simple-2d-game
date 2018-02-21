#include "Controls.h"

#ifdef _DEBUG
#include <iostream>
#endif


void Controls::onHover()
{
#ifdef _DEBUG
	std::cout << "onHover() called" << std::endl;
#endif
	if (onHoverOperation != nullptr)
		onHoverOperation(*this);
}

void Controls::onClick()
{
#ifdef _DEBUG
	std::cout << "onClick() called" << std::endl;
#endif
	if (onClickOperation != nullptr)
		onClickOperation(*this);
}

void Controls::onLeft()
{
#ifdef _DEBUG
	std::cout << "onLeft() called" << std::endl;
#endif
	if (onLeftOperation != nullptr)
		onLeftOperation(*this);
}

bool Controls::isHover(sf::RenderWindow& window) const
{
	sf::Mouse mouse;
	auto position = static_cast<sf::Vector2f> (mouse.getPosition(window));
	return text.getGlobalBounds().contains(position);
}


Controls::Controls(std::string str, sf::Font& font, unsigned int size) :text(str, font, size), alignedTo(nullptr),
topAlignedControl(nullptr), bottomAlignedControl(nullptr), leftAlignedControl(nullptr), rightAlignedControl(nullptr),
onHoverOperation(nullptr), onClickOperation(nullptr), normalColor(sf::Color::White), hoverColor(sf::Color::White),
clickColor(sf::Color::White), currentState(State::normal), alignmentType(Alignment::none), offset()
{
}

const Controls& Controls::getReference() const noexcept
{
	return *this;
}

void Controls::setNormalColor(sf::Color color) noexcept
{
	normalColor = color;
}

void Controls::setHoverColor(sf::Color color) noexcept
{
	hoverColor = color;
}

void Controls::setClickColor(sf::Color color) noexcept
{
	clickColor = color;
}

void Controls::alignFree() noexcept
{
	if (alignedTo == nullptr)return;
	switch (alignmentType)
	{
	case Alignment::none:
		break;
	case Alignment::top:
		alignedTo->topAlignedControl = nullptr;
		break;
	case Alignment::bottom: 
		alignedTo->bottomAlignedControl = nullptr;
		break;
	case Alignment::left:
		alignedTo->leftAlignedControl = nullptr;
		break;
	case Alignment::right:
		alignedTo->rightAlignedControl = nullptr;
		break;
	default: ;
	}
	alignedTo = nullptr;
	alignmentType = Alignment::none;
}

void Controls::setOnHover(std::function<void(Controls&)> operation)
{
	onHoverOperation = operation;
}

void Controls::setOnClick(std::function<void(Controls&)> operation)
{
	onClickOperation = operation;
}

void Controls::setOnLeft(std::function<void(Controls&)> operation)
{
	onLeftOperation = operation;
}

void Controls::setText(std::string str)
{
	text.setString(str);
}

const sf::Font* Controls::getFont() const
{
	return text.getFont();
}


std::string Controls::getText() const
{
	return text.getString();
}

sf::Vector2f Controls::getOffset() const
{
	return offset;
}

void Controls::setFont(const sf::Font& font)
{
	text.setFont(font);
}