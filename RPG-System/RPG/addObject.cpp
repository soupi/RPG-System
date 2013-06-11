#include "addObject.h"
#include "LocalMap.h"

bool addObjScript::Update(Controller&, float elapsedTime)
{
	_localmap.addGameObject(_obj, _pos);
	return false;
}