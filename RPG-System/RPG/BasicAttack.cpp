#include "BasicAttack.h"
#include "LocalMap.h"
#include "remObject.h"


const float EXISTANCE_TIME = 1.f;

void BasicAttack::Update(Controller& ctrl, LocalMap& localmap, float elapsedTime)
{

	sf::FloatRect box = getCollisionBox();
	localmap.Act(*this, box);

	localmap.addCommand(shared_ptr<Script>(new remObjScript(localmap, this)));
}