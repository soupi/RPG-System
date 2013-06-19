#include "Dialog.h"
#include "Macros.h"
#include <algorithm>

// constructor: gets string to show (the dialog will only show the current line each time),
// outer rectangle color and the outlines color
Dialog::Dialog(const string& str, const sf::Color& rect_color, const sf::Color& outline_color) : _dialogbox(str, rect_color, outline_color), _str(str)
{
	std::replace(_str.begin(), _str.end(), ';', '\n'); // break long line to paragraph
}
// when entering the dialog
void Dialog::enter(Hero& hero)
{
	// stop the hero from moving
	hero.getHeroForMap()->stop();
	// set the dialogbox text
	_dialogbox.setString(_str);
}
// handle events
bool Dialog::handleEvents(const Control& controls)
{
	// get new line if A
	if (controls.isPressed(A))
		_continue = _dialogbox.newLine();
	
	return _continue;
}
// updated the dialog
bool Dialog::Update(Controller& ctrl, float elapsedTime)
{
	if (!_continue)
		return false;

	_dialogbox.Update(ctrl, elapsedTime);
	return _continue;
}
void Dialog::Render(Controller& ctrl)
{
	_dialogbox.Render(ctrl);
}
void Dialog::exit()
{
}