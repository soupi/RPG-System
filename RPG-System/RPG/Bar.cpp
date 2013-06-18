#include "Bar.h"
#include "Controller.h"
#include "Bank.h"
#include <sstream>

const float MARGIN = 4.f;

// constructor: gets the base amount of the bar (value at 100%), size and if you would like it's colors to change (default = true)
Bar::Bar(unsigned base, sf::Vector2f& size, bool color) : _base(base), _value(base), _display_colors(color)
{
	_rect.setSize(size);
	_rect.setFillColor(sf::Color::Color(0,0,0,120)); // half transperent black
	_rect.setOutlineColor(sf::Color::White);
	_rect.setOutlineThickness(MARGIN/2);
	_bar.setSize(size - sf::Vector2f(MARGIN*2, MARGIN*2));

	_color = sf::Color::White;
	setColor();
	setBarValue();
	
}

// set the value
void Bar::setValue(int value)
{
	// handle borders
	if (value > int(_base))
		_value = _base;
	else if (value < 0)
		_value = 0;
	else _value = value; // set value

	setColor(); // change color
	setBarValue(); // set bar amount
}

// set bar value
void Bar::setBarValue()
{
	float precent = float(_value)/_base;
	// set the bar's width as the precentage
	_bar.setSize(sf::Vector2f(precent * (_rect.getSize().x - MARGIN * 2) ,_bar.getSize().y));
}

// change color according to value (if _display_colors is set to true)
void Bar::setColor()
{
	if (!_display_colors)
		return;
	if (_value > 0.6f * _base)
		_color = sf::Color::Color(65,195,98, 200);	 // green
	else if (_value > 0.3f * _base)
		_color = sf::Color::Color(230,240,130, 200); // yellow
	else if (_value <= 0.3f * _base)
		_color = sf::Color::Color(250,100,100, 200); // red
	_bar.setFillColor(_color);
}

// show the bar on controller at position
void Bar::show(Controller& ctrl, const sf::Vector2f& position)
{
	setPosition(position);
	
	ctrl.getWindow().draw(_rect);
	ctrl.getWindow().draw(_bar);

	// display value:

	// convert unsigned to string
	std::stringstream strs;
	string val;
	strs << _value;
	strs >> val;
	// --------------------------
	sf::Text text(val, Bank<sf::Font>::getInstance().get("resources/consola.ttf"), (unsigned)_bar.getSize().y);
	text.setPosition(_bar.getPosition() + sf::Vector2f(_rect.getSize().x/2 - text.getCharacterSize(),-3.f));
	text.setColor(sf::Color::White);

	ctrl.getWindow().draw(text);
	// ---------
}

// set bar position
void Bar::setPosition(const sf::Vector2f& pos)
{
	_rect.setPosition(pos);
	_bar.setPosition(pos + sf::Vector2f(MARGIN, MARGIN));
}