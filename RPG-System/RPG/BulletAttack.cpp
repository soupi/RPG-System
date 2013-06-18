#include "BulletAttack.h"
#include "LocalMap.h"
#include "remObject.h"

// like Attack::act but terminates itself at contact



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
// ----------------------------

// update
void BulletAttack::Update(Controller& ctrl, LocalMap& localmap, float elapsedTime)
{
	GameObject::Update(ctrl, localmap, elapsedTime); // move and such
	if (!_moved) // if we haven't move we should be removed.
		localmap.addCommand(shared_ptr<Script>(new remObjScript(localmap, this)));
	localmap.Act(*this, getCollisionBox()); // try to attack
	
}