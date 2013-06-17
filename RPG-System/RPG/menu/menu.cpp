/*
 * Source file for class Menu.
*/
#include "Menu.h"
#include "Button.h"
#include "../Utility.h"
#include <exception>

// Menu's outer rectangle's border thickness 
const float OUTLINE_THICKNESS = 2.f;


// Constructor sets the location and size of the menu
// size is the number of buttons in each row and column
// gets: location, size and button texture filename
Menu::Menu(const sf::Vector2f& loc, const sf::Vector2f& size, unsigned button_height) 
			: _size(size), _pos(loc), _button_height(button_height), _marked_btn(BAD)
{
}

// add new button
// gets: pic mark on texture and command to execute
// return success
bool Menu::add(const string& text, Command* cmd)
{
	// if the buttons space is full
	if (unsigned(_size.x*_size.y) <= _buttons.size())
		return false;

	// set new location
	if (unsigned(_size.x) == 0)
		throw std::exception("can't divide button size by zero");

	sf::Vector2f loc(_pos.x, _pos.y + _button_height*_buttons.size());

	// create button
	_buttons.push_back(shared_ptr<Button>(new Button(loc, text, cmd)));

	return true;
}

// draws buttons on screen
void Menu::display(sf::RenderWindow& window)
{
	for (unsigned i = 0; i < _buttons.size(); i++)
		_buttons[i]->display(window);
}

// execute button's command currently pressed
// gets: location pressed
// returns: success
bool Menu::execute()
{
	bool executed = false;

	// execute current marked button
	if (_marked_btn != BAD && _buttons[_marked_btn]->execute())
		executed = true;

	return executed;
}

// change marked button
void Menu::markNext()
{
	// unmark current button
	if (BAD < _marked_btn && _marked_btn < int(_buttons.size()))
		_buttons[_marked_btn]->unmark();

	if (_marked_btn <= BAD) // or first if none was marked
		_marked_btn = 0;
	else 
		_marked_btn = _marked_btn +1;

	if (_marked_btn >= int(_buttons.size()))
		_marked_btn = BAD;

	// mark
	if (BAD < _marked_btn && _marked_btn < int(_buttons.size()))
		_buttons[_marked_btn]->mark();
}

void Menu::markPrev()
{
	// unmark current button
	if (BAD < _marked_btn && _marked_btn < int(_buttons.size()))
		_buttons[_marked_btn]->unmark();

	
	if (_marked_btn <= BAD) // or last if none was marked
		_marked_btn = _buttons.size() -1;
	else 
		_marked_btn = _marked_btn -1;

	// mark
	if (BAD < _marked_btn && _marked_btn < int(_buttons.size()))
		_buttons[_marked_btn]->mark();
}