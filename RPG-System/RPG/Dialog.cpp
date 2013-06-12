#include "Dialog.h"
#include "Macros.h"
#include <algorithm>

Dialog::Dialog(const string& str) : _dialogbox(str), _str(str)
{
	std::replace(_str.begin(), _str.end(), ';', '\n');
	_continue = true;
}
void Dialog::enter(Hero& hero)
{
	_dialogbox.setString(_str);
	_continue = true;
}
bool Dialog::handleEvents(const Control& controls)
{
	if (controls.isPressed(A))
		_continue = _dialogbox.newLine();
	
	return _continue;
}
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
	_continue = false;
}