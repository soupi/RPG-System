#pragma once

#include "LocalObject.h"


class NPC : public LocalObject
{
public:
	NPC(shared_ptr<Script> script, Graphics* graphics = new NoGraphics, Movement* movement = new NoMovement,
		bool passable = false) : LocalObject(script, graphics, movement, passable) {}

	virtual void StepOn(LocalMap& localmap, HeroCharacter&);
};