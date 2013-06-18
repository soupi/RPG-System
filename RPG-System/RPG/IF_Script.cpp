#include "IFScript.h"

// sets which script to run
void IFScript::enter(Hero& hero)
{
	_if = check(hero);

	if (_if)
		_if_script->Enter(hero);
	else _else_script->Enter(hero);

}
// handle events for winning script
bool IFScript::handleEvents(const Control& controls)
{
	if (_if)
	{
		_continue = _if_script->handleEvents(controls);
		return _continue;
	}
	
	_continue = _else_script->handleEvents(controls);
	return _continue;
}
// dido
bool IFScript::Update(Controller& ctrl, float elapsedTime)
{
	if (_if)
	{
		_continue = _if_script->Update(ctrl, elapsedTime);
		return _continue;
	}
	_continue = _else_script->Update(ctrl, elapsedTime);
	return _continue;
}
// dido
void IFScript::Render(Controller& ctrl)
{
	if (_if)
		_if_script->Render(ctrl);
	else _else_script->Render(ctrl);
}
// dido
void IFScript::exit()
{
	if (_if)
		_if_script->Exit();
	else _else_script->Exit();
}

// check implemented for IFLevel class
bool IFLevel::check(Hero& hero)
{
	return (hero.getHeroData()->heroLevel() >= _level);
}
// check implemented for IFQItem class
bool IFQItem::check(Hero& hero)
{
	return hero.getHeroData()->hasQuestItem(_item_name);
}