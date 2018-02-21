#include "Button.h"

sf::Vector2f Button::getCenter() const
{
	auto x = text.getGlobalBounds().width / 2;
	auto y = text.getGlobalBounds().height / 2;
	return sf::Vector2f(x, y);
}

void Button::checkAlignment(Controls& control)
{
	if(control.alignedTo==this)
	{
		control.alignFree();
	}
}

Button::Button(std::string str, sf::Font& font, unsigned int size) :Controls(str, font, size)
{
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(text);
}

void Button::eventhandler(sf::Event& event, sf::RenderWindow& window)
{
	switch (event.type)
	{
	case sf::Event::MouseMoved:
		if (currentState == State::pressed && isHover(window) == true)
		{
		}
		else if (currentState == State::hovered && isHover(window) == true)
		{
		}
		else if (isHover(window) == true)
		{
			currentState = State::hovered;
			text.setFillColor(hoverColor);
			onHover();
		}
		else if (currentState == State::hovered || currentState == State::pressed && isHover(window) == false)
		{
			currentState = State::normal;
			text.setFillColor(normalColor);
			onLeft();
		}
		break;

	case sf::Event::MouseButtonPressed:
		if (currentState == State::hovered)
		{
			currentState = State::pressed;
			text.setFillColor(clickColor);
		}
		break;

	case sf::Event::MouseButtonReleased:
		if (currentState == State::pressed)
		{
			currentState = State::hovered;
			text.setFillColor(hoverColor);
			onClick();
		}
		break;

	default:;
	}
}

void Button::setPosition(const float& x, const float& y)
{
	alignFree();
	text.setPosition(x, y);
	offset = sf::Vector2f(x, y);
	update();
}

void Button::setPosition(const sf::Vector2f& pos)
{
	alignFree();
	text.setPosition(pos.x, pos.y);
	offset = pos;
	update();
}

void Button::alignToTop(Controls& control, sf::Vector2f offset)
{
	this->alignFree();
	alignmentType = Alignment::top;
	this->offset = offset;
	control.topAlignedControl = this;
	auto position = control.getPosition();
	position.x += control.getCenter().x / 2 - this->getCenter().x / 2;
	position.x += offset.x;
	position.y -= control.getGlobalBounds().height;
	position.y += offset.y;
	this->text.setPosition(position);
	alignedTo = &control;
	update();
}

void Button::alignToBottom(Controls& control, sf::Vector2f offset)
{
	this->alignFree();
	alignmentType = Alignment::bottom;
	this->offset = offset;
	control.bottomAlignedControl = this;
	auto position = control.getPosition();
	position.x += control.getCenter().x / 2 - this->getCenter().x / 2;
	position.x += offset.x;
	position.y += getGlobalBounds().height;
	position.y += offset.y;
	this->text.setPosition(position);
	alignedTo = &control;
	update();
}

void Button::alignToLeft(Controls& control, sf::Vector2f offset)
{
	this->alignFree();
	alignmentType = Alignment::left;
	this->offset = offset;
	control.leftAlignedControl = this;
	auto position = control.getPosition();
	position.x -= getGlobalBounds().width;
	position.x += offset.x;
	position.y += control.getCenter().y / 2 - this->getCenter().y / 2;
	position.y += offset.y;
	this->text.setPosition(position);
	alignedTo = &control;
	update();
}

void Button::alignToRight(Controls& control, sf::Vector2f offset)
{
	this->alignFree();
	alignmentType = Alignment::right;
	this->offset = offset;
	control.rightAlignedControl = this;
	auto position = control.getPosition();
	position.x += control.getGlobalBounds().width;
	position.x += offset.x;
	position.y += control.getCenter().y / 2 - this->getCenter().y / 2;
	position.y += offset.y;
	this->text.setPosition(position);
	alignedTo = &control;
	update();
}

sf::Vector2f Button::getPosition() const
{
	return text.getPosition();
}

sf::FloatRect Button::getGlobalBounds() const
{
	return text.getGlobalBounds();
}

void Button::update()
{
	if (bottomAlignedControl != nullptr)
		bottomAlignedControl->alignToBottom(*this, bottomAlignedControl->offset);
	if (topAlignedControl != nullptr)
		topAlignedControl->alignToTop(*this, topAlignedControl->offset);
	if (leftAlignedControl != nullptr)
		leftAlignedControl->alignToLeft(*this, leftAlignedControl->offset);
	if (rightAlignedControl != nullptr)
		rightAlignedControl->alignToRight(*this, rightAlignedControl->offset);
}
