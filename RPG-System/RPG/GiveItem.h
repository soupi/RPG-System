#pragma once

#include "Script.h"
#include <string>
#include <memory>
#include "HeroCharacter.h"
#include "QuestItem.h"

using std::shared_ptr;
using std::string;

class GiveItem : public Script
{
public:
	GiveItem(const string& item_name) : _item(item_name) { }
	virtual bool handleEvents(const Control& controls) { return _continue; }
	virtual bool Update(Controller&, float elapsedTime) { _hero->giveQuestItem(_item);  } 
	virtual void Render(Controller& ctrl);

private:
	QuestItem _item;
	shared_ptr<HeroCharacter> _hero;
	

	virtual void enter(Hero& hero) { _hero = hero.getHeroForMap(); }
	virtual void exit();
};