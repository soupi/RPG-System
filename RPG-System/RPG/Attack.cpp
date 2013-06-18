#include "Attack.h"
#include "LocalObject.h"
#include "LocalMap.h"
#include "remObject.h"


bool Attack::act(LocalMap& localmap, LocalObject& obj)
{
	return true;
}

bool Attack::act(LocalMap& localmap, Enemy& obj)
{
	if (!_attacked)
		_atk->act(localmap, *this, obj);
	return true;
}
bool Attack::act(LocalMap& localmap, HeroCharacter& obj)
{
	if (!_attacked)
		_atk->act(localmap, *this, obj);
	return true;
}

void Attack::attack(LocalMap& localmap, Enemy& obj)
{
	obj.attack(_stats, _power);
	_attacked = true;
}

void Attack::attack(LocalMap& localmap, HeroCharacter& obj)
{
	obj.attack(_stats, _power);
	_attacked = true;
}
void Attack::attack(LocalMap& localmap, LocalObject& obj)
{

}

