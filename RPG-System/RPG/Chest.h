#pragma once

#include <SFML/Graphics.hpp>
#include "LocalObject.h"
#include "IFScript.h"
#include "GiveItem.h"
#include <string>
#include "LocalMap.h"

using std::string;

class Chest : public LocalObject
{
public:
	Chest(const string& item_name) : _item_name(item_name), LocalObject(shared_ptr<Script>(new IFQItem(item_name, shared_ptr<Script>(new NoScript), shared_ptr<Script>(new GiveItem(item_name)))),
		 new NoGraphics, new NoMovement, false) {}

	virtual void act(LocalMap& localmap, HeroCharacter& hero)
	{
		if (!hero.hasQuestItem(_item_name))
			localmap.addScript(_script);
	}
	virtual void StepOn(LocalMap& localmap, HeroCharacter&) {}
private:
	string _item_name;
};