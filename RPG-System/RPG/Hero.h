#pragma once


#include "Stats.h"
#include "HeroCharacter.h"

class Hero 
{
public:
	HeroCharacter* getHeroForMap() { return &_hero; }



private:
	HeroCharacter _hero;
	unsigned _exp;
	unsigned _level;
	unsigned _coins;
	// vector<Item*> _items;
	// vector<Quest_Item*> _quest_items;
	
	unsigned _HP;
	int _Lives;
	Stats _stats;
	
};

