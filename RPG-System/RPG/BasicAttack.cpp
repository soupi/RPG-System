#include "BasicAttack.h"
#include "LocalMap.h"
#include "remObject.h"


const float EXISTANCE_TIME = PRESS_INTERVAL;

// update attack
void BasicAttack::Update(Controller& ctrl, LocalMap& localmap, float elapsedTime)
{
	_life_timer += elapsedTime; // after EXISTANCE_TIME has passed the attack will ask to be deleted

	if (_first) // only try to attack on first update
	{
		sf::FloatRect box = getCollisionBox();
		localmap.Act(*this, box);
	}
	if (EXISTANCE_TIME < _life_timer) // my life time is over, please remove me.
		localmap.addCommand(shared_ptr<Script>(new remObjScript(localmap, this)));
}