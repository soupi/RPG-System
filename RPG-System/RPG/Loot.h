#pragma once

// Loot is an object dropped by killing an enemy. it contains expirience points and coins.
// you can pick it up when you step on it.

#include <SFML/Graphics.hpp>
#include "LocalObject.h"
#include <string>
#include "LocalMap.h"
#include "NoScript.h"
#include "StaticGraphics.h"
#include "Bank.h"

using std::string;

class Loot : public LocalObject
{
public:
	Loot(unsigned exp, unsigned coins) : LocalObject(shared_ptr<Script>(new NoScript),
		new StaticGraphics(&(Bank<sf::Texture>::getInstance().get("resources/art/loot.png")), sf::Vector2i(0,0), sf::Vector2u(16,16)),
		new NoMovement, true), _exp(exp), _coins(coins) {}

	// when stepped on. gives the hero it's contents and remove itself from the map.
	virtual void StepOn(LocalMap& localmap, HeroCharacter& hero)
	{
		hero.Loot(localmap, _exp, _coins);
		localmap.addCommand(shared_ptr<Script>(new remObjScript(localmap, this)));
	}
	// does the same when interacted
	virtual bool act(LocalMap& localmap, HeroCharacter& hero) 
	{
		StepOn(localmap, hero);
		return true;
	}
private:
	unsigned _exp;
	unsigned _coins;
};