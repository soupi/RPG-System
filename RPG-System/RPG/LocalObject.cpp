#include "LocalObject.h"
#include "LocalMap.h"

bool LocalObject::act(LocalMap& localmap, HeroCharacter&)
{
	localmap.addScript(_script);
	return true;
}