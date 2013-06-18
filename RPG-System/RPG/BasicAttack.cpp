#include "BasicAttack.h"
#include "LocalMap.h"
#include "remObject.h"


const float EXISTANCE_TIME = PRESS_INTERVAL;

void BasicAttack::Update(Controller& ctrl, LocalMap& localmap, float elapsedTime)
{
	_life_timer += elapsedTime;

	if (_first)
	{
		sf::FloatRect box = getCollisionBox();
		localmap.Act(*this, box);
	}
	if (EXISTANCE_TIME < _life_timer)
		localmap.addCommand(shared_ptr<Script>(new remObjScript(localmap, this)));
}