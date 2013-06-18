#pragma once

// a chest contains an item. you get it when you interact with it.

#include <SFML/Graphics.hpp>
#include "LocalObject.h"
#include "IFScript.h"
#include "GiveItem.h"
#include <string>
#include "LocalMap.h"
#include "StaticGraphics.h"

using std::string;

class Chest : public LocalObject
{
public:
	Chest(const string& item_name) : _item_name(item_name), LocalObject(shared_ptr<Script>(new IFQItem(item_name, shared_ptr<Script>(new NoScript), shared_ptr<Script>(new GiveItem(item_name)))),

		new StaticGraphics(&(Bank<sf::Texture>::getInstance().get("resources/art/chest.png")), sf::Vector2i(0,0), sf::Vector2u(TILE_SIZE,TILE_SIZE)), new NoMovement, false) {}

	virtual bool act(LocalMap& localmap, HeroCharacter& hero)
	{
		if (!hero.hasQuestItem(_item_name))
			localmap.addScript(_script);

		// open chest (graphically)
		sf::Vector2f pos = getPos();
		setGraphics(new StaticGraphics(&(Bank<sf::Texture>::getInstance().get("resources/art/chest.png")), sf::Vector2i(0,1), sf::Vector2u(TILE_SIZE,TILE_SIZE)));
		setPos(pos);

		return true;
	}
	virtual void StepOn(LocalMap& localmap, HeroCharacter&) {}
private:
	string _item_name;
};