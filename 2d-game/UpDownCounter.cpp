#include "UpDownCounter.h"



UpDownCounter::UpDownCounter(std::string str, sf::Font& font, unsigned int size): Controls(str,font,size)
{
	left.setFillColor(text.getFillColor());
	left.setString("<-\t");
	left.setPosition(sf::Vector2f(text.getPosition().x - left.getGlobalBounds().width, text.getPosition().y));

	right.setFillColor(text.getFillColor());
	right.setString("\t->");
	left.setFillColor(text.getFillColor());
	left.setString("<-\t");
	left.setPosition(sf::Vector2f(text.getPosition().x + text.getGlobalBounds().width, text.getPosition().y));
}


UpDownCounter::~UpDownCounter()
{
}

void UpDownCounter::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

}
