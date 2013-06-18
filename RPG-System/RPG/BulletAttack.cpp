#include "BulletAttack.h"
#include "LocalMap.h"
#include "remObject.h"

bool BulletAttack::act(LocalMap& localmap, LocalObject& obj)
{
	if (!obj.canStepOn(*this))
		localmap.addCommand(shared_ptr<Script>(new remObjScript(localmap, this)));
	return true;
}
bool BulletAttack::act(LocalMap& localmap, Enemy& obj)
{
	Attack::act(localmap, obj);
	localmap.addCommand(shared_ptr<Script>(new remObjScript(localmap, this)));
	return true;
}

bool BulletAttack::act(LocalMap& localmap, HeroCharacter& obj)
{
	Attack::act(localmap, obj);
	localmap.addCommand(shared_ptr<Script>(new remObjScript(localmap, this)));
	return true;
}


void BulletAttack::Update(Controller& ctrl, LocalMap& localmap, float elapsedTime)
{
	GameObject::Update(ctrl, localmap, elapsedTime);
	if (!_moved)
		localmap.addCommand(shared_ptr<Script>(new remObjScript(localmap, this)));
	localmap.Act(*this, getCollisionBox());
	
}