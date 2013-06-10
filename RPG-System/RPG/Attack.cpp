#include "Attack.h"
#include "LocalObject.h"
#include "LocalMap.h"
#include "remObject.h"

void Attack::StepOn(LocalMap& localmap, LocalObject& obj)
{
	if (obj.canStepOn(*this))
		return;

	localmap.addScript(shared_ptr<Script>(new remObjScript(localmap, this)));
}

void Attack::StepOn(LocalMap& localmap, Enemy& obj)
{
	_atk->StepOn(localmap, *this, obj);
}
void Attack::StepOn(LocalMap& localmap, HeroCharacter& obj)
{
	_atk->StepOn(localmap, *this, obj);
}

void Attack::attack(LocalMap& localmap, Enemy& obj)
{
	
}
void Attack::attack(LocalMap& localmap, HeroCharacter& obj)
{

}