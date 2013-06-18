#include "LocalObject.h"
#include "LocalMap.h"

// function to execute when hero pressed on it
// returns if an action has accured
bool LocalObject::act(LocalMap& localmap, HeroCharacter&)
{
	localmap.addScript(_script); // add my script to the local map
	return true;
}