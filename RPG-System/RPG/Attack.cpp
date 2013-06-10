#include "Attack.h"
#include "LocalObject.h"
#include "LocalMap.h"
#include "remObject.h"

void Attack::StepOn(LocalMap& localmap, LocalObject& obj)
{
	if (obj.canStepOn(*this))
		return;

	localmap.addScript(shared_ptr<Script>(new remObjScript(localmap, this)));
}