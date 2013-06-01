#include "IFScript.h"

void IFScript::enter(Hero& hero)
{
	_if = check(hero);
	_check = true;
	_continue = true;
	if (_if)
		_if_script->Enter(hero);
	else _else_script->Enter(hero);

}

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
void IFScript::Render(Controller& ctrl)
{
	if (_if)
		_if_script->Render(ctrl);
	else _else_script->Render(ctrl);
}
void IFScript::exit()
{
	_continue = false;
	if (_if)
		_if_script->Exit();
	else _else_script->Exit();
}

bool IFLevel::check(Hero& hero)
{
	return (hero.getHeroData()->heroLevel() >= _level);
}

bool IFQItem::check(Hero& hero)
{
	return hero.getHeroData()->hasQuestItem(_item_name);
}