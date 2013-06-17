/*
 * Header file for class Menu.
*/
#pragma once

#include <string>
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include "../Macros.h"
#include "Command.h"
#include "../Control.h"

using std::string;
using std::shared_ptr;

class Button; // forward class declaration

class Menu
{
public:
	Menu(const sf::Vector2f& loc, const sf::Vector2f& size, unsigned button_height);
	void display(sf::RenderWindow& window);
	bool add(const string& text, Command* cmd); // add button
	bool execute(); 
	void markNext();
	void markPrev();
private:
	std::vector <shared_ptr<Button>> _buttons; // buttons
	sf::Vector2f _size; // menu size
	sf::Vector2f _pos;

	unsigned _button_height;
	int _marked_btn;
};
