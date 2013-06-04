#include "Scripts.h"

bool Scripts::handleEvents(const Control& controls)
{
	_scripts[_current]->handleEvents(controls);
	return false;
}
bool Scripts::Update(Controller& ctrl, float elapsedTime)
{
	if (! _scripts[_current]->Update(ctrl, elapsedTime))
		return Switch();
	return true;
}
void Scripts::Render(Controller& ctrl)
{
	_scripts[_current]->Render(ctrl);
}

void Scripts::enter(Hero& hero)
{
	_hero = &hero;
	_current = 0;
	_scripts[_current]->Enter(hero);
	_continue = true;
}
void Scripts::exit()
{
	_current = 0;
	_scripts[_current]->Exit();
	_continue = false;
}
bool Scripts::Switch()
{
	_scripts[_current]->Exit();
	++_current;
	if (_current >= _scripts.size())
		return false;
	_scripts[_current]->Enter(*_hero);
	return true;
}