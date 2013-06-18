//this is the Button cpp file

#include "Button.h"
#include <sstream>
#include <iostream>
#include "../Bank.h"

// Constructor:
// gets: location, texture, pic mark on texture and command
Button::Button(const sf::Vector2f& loc, const string& text, Command* cmd) : _is_marked(false), _cmd(cmd)
{
	// init rect and text
	_text.setString(text);
	_text.setFont(Bank<sf::Font>::getInstance().get("resources/consola.ttf"));
	_text.setPosition(loc);
	_text.setCharacterSize(40);
	_rect.setFillColor(sf::Color::Transparent);
	_rect.setOutlineColor(sf::Color::White);
	_rect.setSize(sf::Vector2f(_text.getLocalBounds().width + 10, _text.getLocalBounds().height*1.5f));
	_rect.setPosition(_text.getPosition().x - 5, _text.getPosition().y);
}

// will mark the button 
void Button::mark()
{
	// if not, mark it
	_rect.setOutlineThickness(1.f);
	_is_marked = true;

}

// draw button on window
void Button::display(sf::RenderWindow& window)
{
	if (_is_marked)
		window.draw(_rect);
	window.draw(_text);
}

// set button position
void Button::setPosition(const sf::Vector2f& pos)
{
	_rect.setPosition(pos);
	_text.setPosition(pos);
}

// runs the preseted action if the button is marked
bool Button::execute()
{
	if (!_is_marked)
		return false;

	_cmd->execute();
	return true;
}