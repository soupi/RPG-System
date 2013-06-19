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
}

// will mark the button 
void Button::mark()
{
	// if not, mark it
	_text.setColor(sf::Color::Color(0,160,230,230));
	_is_marked = true;

}

// draw button on window
void Button::display(sf::RenderWindow& window)
{
	window.draw(_text);
}

// set button position
void Button::setPosition(const sf::Vector2f& pos)
{
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