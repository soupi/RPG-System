#include "Dialog.h"
#include "Macros.h"

Dialog::Dialog(const string& str) : _dialogbox(str), _str(str), _clock(0.f)
{
	_continue = true;
}
void Dialog::enter(Hero& hero)
{
	_dialogbox.setString(_str);
	_continue = true;
}
bool Dialog::handleEvents(const Control& controls)
{
	if (_clock > PRESS_INTERVAL)
	{
		if (controls.isPressed(A))
		{
			_continue = _dialogbox.newLine();
			_clock = 0.f;
		}
	}
	return _continue;
}
bool Dialog::Update(Controller& ctrl, float elapsedTime)
{
	_clock += elapsedTime;
	_dialogbox.Update(ctrl, elapsedTime);
	return _continue;
}
void Dialog::Render(Controller& ctrl)
{
	_dialogbox.Render(ctrl);
}
void Dialog::Exit()
{
	_continue = false;
	_entered = false;
}