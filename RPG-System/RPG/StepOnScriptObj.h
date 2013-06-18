#pragma once

// a script that activates when the hero steps on it

#include <SFML/Graphics.hpp>
#include "LocalObject.h"
#include "LocalMap.h"
#include "remObject.h"

class StepOnScriptObj : public LocalObject
{
public:
	StepOnScriptObj(shared_ptr<Script>& script) : LocalObject(script, new NoGraphics, new NoMovement, true) {}

	virtual bool act(LocalMap& localmap, HeroCharacter& hero) { return false; }
	virtual void StepOn(LocalMap& localmap, HeroCharacter&) { localmap.addScript(_script); localmap.addCommand(shared_ptr<Script>(new remObjScript(localmap, this))); }
};