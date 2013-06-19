// header file for Button class

#pragma once

#include <memory>
#include <string>
#include <SFML/Graphics.hpp>
#include "Command.h"
#include "../Macros.h"

using std::shared_ptr;
using std::string;
const unsigned BTN_HEIGHT = 64;

class Button
{
public:
	Button(const sf::Vector2f& loc, const string& text, Command* cmd);
	void display(sf::RenderWindow& window);
	void mark();
	void unmark() { _is_marked = false; _text.setColor(sf::Color::White); }
	void setPosition(const sf::Vector2f& pos);
	bool execute();

private:
	sf::Text _text; // button sprite
	shared_ptr<Command> _cmd; // command
	bool _is_marked;
};
