#include "remObject.h"
#include "LocalMap.h"

bool remObjScript::Update(Controller&, float elapsedTime)
{
	_localmap.map()->remGameObject(_obj);
	_obj = NULL;
	return false;
}