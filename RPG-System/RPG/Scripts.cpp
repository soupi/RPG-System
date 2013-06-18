#include "Scripts.h"


// handle events for current script
bool Scripts::handleEvents(const Control& controls)
{
	_scripts[_current]->handleEvents(controls);
	return false;
}
// updated current script
bool Scripts::Update(Controller& ctrl, float elapsedTime)
{
	// if script is done, switch script
	if (! _scripts[_current]->Update(ctrl, elapsedTime))
		return Switch();
	return true;
}
// render current
void Scripts::Render(Controller& ctrl)
{
	_scripts[_current]->Render(ctrl);
}

// enter first script
void Scripts::enter(Hero& hero)
{
	_hero = &hero;
	_current = 0;
	_scripts[_current]->Enter(hero);
}
// exit current script and reset
void Scripts::exit()
{
	_current = 0;
	_scripts[_current]->Exit();

}
// switch to next script or return false if there isn't one
bool Scripts::Switch()
{
	_scripts[_current]->Exit();
	++_current;

	if (_current >= _scripts.size())
		return false;

	_scripts[_current]->Enter(*_hero);
	return true;
}