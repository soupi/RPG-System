#pragma once

#include <SFML\Graphics.hpp>

class Controller;

class Bar 
{
public:
	Bar(unsigned base = 100, sf::Vector2f& size = sf::Vector2f(400, 40), bool color = true);
	void setValue(unsigned value);
	void show(Controller& ctrl, const sf::Vector2f& pos);
	void setPosition(sf::Vector2f&);

private:
	unsigned _base;
	unsigned _value;

	bool _display_colors;

	sf::RectangleShape _rect;
	sf::RectangleShape _bar;
	sf::Color _color;

	void setColor();
	void setBarValue();
};
