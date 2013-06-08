#include "Bar.h"
#include "Controller.h"
#include "Bank.h"
#include <sstream>

const float PADDING = 4.f;

Bar::Bar(unsigned base, sf::Vector2f& size, bool color) : _base(base), _value(base), _display_colors(color)
{
	_rect.setSize(size);
	_rect.setFillColor(sf::Color::Color(0,0,0,120));
	_rect.setOutlineColor(sf::Color::White);
	_rect.setOutlineThickness(PADDING/2);
	_bar.setSize(size - sf::Vector2f(PADDING*2, PADDING*2));

	_color = sf::Color::White;
	setColor();
	setBarValue();
	
}

void Bar::setValue(unsigned value)
{
	if (value > _base)
		_value = _base;
	else _value = value;

	setColor();
	setBarValue();
}
void Bar::setBarValue()
{
	float precent = float(_value)/_base;
	_bar.setSize(sf::Vector2f(precent * (_rect.getSize().x - PADDING * 2) ,_bar.getSize().y));
}

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


void Bar::show(Controller& ctrl, sf::Vector2f& position)
{


	setPosition(position);
	
	ctrl.getWindow().draw(_rect);
	ctrl.getWindow().draw(_bar);


	// convert unsigned to string
	std::stringstream strs;
	string val;
	strs << _value;
	strs >> val;
	// --------------------------

	sf::Text text(val, Bank<sf::Font>::getInstance().get("resources/consola.ttf"), (unsigned)_bar.getSize().y - 2);
	text.setPosition(_bar.getPosition() + sf::Vector2f(_rect.getSize().x/2 - text.getCharacterSize(),-3.f));
	text.setColor(sf::Color::White);

	ctrl.getWindow().draw(text);

}

void Bar::setPosition(sf::Vector2f& pos)
{
	_rect.setPosition(pos);
	_bar.setPosition(pos + sf::Vector2f(PADDING, PADDING));
}