#include "LocalObject.h"

void LocalObject::Interact(LocalMap& localmap, GameObject& obj)
{

}

void LocalObject::StepOn(LocalMap& localmap, GameObject& obj)
{

}

bool LocalObject::canStepOn(GameObject& obj)
{
	return _passable;
}