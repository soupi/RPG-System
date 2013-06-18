#include "remObject.h"
#include "LocalMap.h"

// update
bool remObjScript::Update(Controller&, float elapsedTime)
{
	// remove the object
	_localmap.remGameObject(_obj);
	_obj = NULL; // unpoint
	_continue = false; // ask to exit me
	return false;
}