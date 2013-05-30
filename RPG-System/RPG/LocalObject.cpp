#include "LocalObject.h"
#include "LocalMap.h"

void LocalObject::act(LocalMap& localmap, HeroCharacter&)
{
	localmap.addScript(_script);
}