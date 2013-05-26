#pragma once


#include "Stats.h"
#include "HeroCharacter.h"

using std::shared_ptr;

class Hero 
{
public:
	Hero() : _hero( new HeroCharacter) { }
	shared_ptr<HeroCharacter>& getHeroForMap() { return _hero; }



private:
	shared_ptr<HeroCharacter> _hero;
	unsigned _exp;
	unsigned _level;
	unsigned _coins;
	// vector<Item*> _items;
	// vector<Quest_Item*> _quest_items;
	
	unsigned _HP;
	int _Lives;
	Stats _stats;
	
};

