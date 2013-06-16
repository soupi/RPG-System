#pragma once

#include <SFML/Graphics.hpp>
#include "LocalObject.h"
#include "ChangeMap.h"
#include <string>
#include "LocalMap.h"

using std::string;

class Door : public LocalObject
{
public:
	Door(const string& map, unsigned starting_tile) : LocalObject(shared_ptr<Script>(new ChangeMap(map, starting_tile)),
		 new NoGraphics, new NoMovement, true) {}

	virtual void act(LocalMap& localmap, HeroCharacter& hero) {	localmap.addScript(_script); }
	virtual void StepOn(LocalMap& localmap, HeroCharacter&) { localmap.addScript(_script); }
};