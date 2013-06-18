#pragma once

// this script will give an item to the hero 

#include "Script.h"
#include <string>
#include <memory>
#include "HeroCharacter.h"
#include "QuestItem.h"
#include "Dialog.h"

using std::shared_ptr;
using std::string;

class GiveItem : public Script
{
public:
	GiveItem(const string& item_name) : _item(item_name), _info("You have received an Item: \"" + item_name + "\"!") { }
	// handle events for _info dialog
	virtual bool handleEvents(const Control& controls) { return _info.handleEvents(controls); }
	// give quest item if the hero doesn't have it and say that the hero got it.
	virtual bool Update(Controller& ctrl, float elapsedTime) 
	{ 
		if (!_hero->hasQuestItem(_item.name()))
			_hero->giveQuestItem(_item);
		_continue = _info.Update(ctrl, elapsedTime);
		return _continue;
	} 
	virtual void Render(Controller& ctrl) 
	{
		_info.Render(ctrl);
	}

private:
	QuestItem _item;
	shared_ptr<HeroCharacter> _hero;
	Dialog _info;
	
	virtual void enter(Hero& hero) { _hero = hero.getHeroForMap(); _info.Enter(hero); }
	virtual void exit() { _info.Exit(); }
};