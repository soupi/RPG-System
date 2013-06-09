#pragma once

#include <SFML/Graphics.hpp>
#include "LocalObject.h"
#include <string>
#include "LocalMap.h"
#include "NoScript.h"

using std::string;

class Loot : public LocalObject
{
public:
	Loot(unsigned exp, unsigned coins) : LocalObject(shared_ptr<Script>(new NoScript),
		 new NoGraphics, new NoMovement, true), _exp(exp), _coins(coins) {}

	virtual void StepOn(LocalMap& localmap, HeroCharacter& hero)
	{
		hero.Loot(localmap, _exp, _coins);
		localmap.addScript(shared_ptr<Script>(new remObjScript(localmap, this)));
	}
	virtual void act(LocalMap& localmap, HeroCharacter&) {}
private:
	unsigned _exp;
	unsigned _coins;
};