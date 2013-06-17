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
	void unmark() { _is_marked = false; _rect.setOutlineThickness(0.f); }
	void setPosition(const sf::Vector2f& pos);
	bool execute();

private:
	sf::RectangleShape _rect; // surrounding rect
	sf::Text _text; // button sprite
	shared_ptr<Command> _cmd; // command
	bool _is_marked;
};
