#include "addObject.h"
#include "LocalMap.h"

// add object to local map
bool addObjScript::Update(Controller&, float elapsedTime)
{
	_localmap.addGameObject(_obj, _pos);
	return false;
}