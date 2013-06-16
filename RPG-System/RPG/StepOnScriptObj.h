#pragma once

#include <SFML/Graphics.hpp>
#include "LocalObject.h"
#include "LocalMap.h"
#include "remObject.h"

class StepOnScriptObj : public LocalObject
{
public:
	StepOnScriptObj(shared_ptr<Script>& script) : LocalObject(script, new NoGraphics, new NoMovement, true) {}

	virtual void act(LocalMap& localmap, HeroCharacter& hero) { }
	virtual void StepOn(LocalMap& localmap, HeroCharacter&) { localmap.addScript(_script); localmap.addCommand(shared_ptr<Script>(new remObjScript(localmap, this))); }
};