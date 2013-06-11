#include "Attack.h"
#include "LocalObject.h"
#include "LocalMap.h"
#include "remObject.h"


void Attack::act(LocalMap& localmap, LocalObject& obj)
{
	if (!obj.canStepOn(*this))
		localmap.addCommand(shared_ptr<Script>(new remObjScript(localmap, this)));
}

void Attack::act(LocalMap& localmap, Enemy& obj)
{
	_atk->act(localmap, *this, obj);
	localmap.addCommand(shared_ptr<Script>(new remObjScript(localmap, this)));
}
void Attack::act(LocalMap& localmap, HeroCharacter& obj)
{
	_atk->act(localmap, *this, obj);
	localmap.addCommand(shared_ptr<Script>(new remObjScript(localmap, this)));
}

void Attack::attack(LocalMap& localmap, Enemy& obj)
{
	obj.attack(_stats, _power);
}

void Attack::attack(LocalMap& localmap, HeroCharacter& obj)
{
	obj.attack(_stats, _power);
}
void Attack::attack(LocalMap& localmap, LocalObject& obj)
{

}

