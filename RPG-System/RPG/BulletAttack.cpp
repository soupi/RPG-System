#include "BulletAttack.h"
#include "LocalMap.h"
#include "remObject.h"

void BulletAttack::Update(Controller& ctrl, LocalMap& localmap, float elapsedTime)
{
	GameObject::Update(ctrl, localmap, elapsedTime);
	if (!_moved)
		localmap.addCommand(shared_ptr<Script>(new remObjScript(localmap, this)));
	localmap.Act(*this, getCollisionBox());
	
}