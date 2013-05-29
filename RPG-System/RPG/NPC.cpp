#include "NPC.h"

#include "LocalMap.h"
#include "HeroCharacter.h"

void NPC::act(LocalMap& localmap, HeroCharacter&)
{
	localmap.addScript(_script);
}
bool NPC::canStepOn(LocalMap& localmap, HeroCharacter&)
{
	return false;
}