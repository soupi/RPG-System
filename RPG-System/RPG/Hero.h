#pragma once

#include "Stats.h"
#include "HeroCharacter.h"
#include "HeroData.h"
#include "QuestItem.h"

#include <string>
#include <map>

using std::shared_ptr;


class Hero 
{
public:
	Hero() : _data(new HeroData), _hero(new HeroCharacter(_data)) { }
	shared_ptr<HeroCharacter>& getHeroForMap() { return _hero; }
	shared_ptr<HeroData>& getHeroData() { return _data; }

	bool isAlive() const { return _data->isAlive(); }


private:
	shared_ptr<HeroData> _data;
	shared_ptr<HeroCharacter> _hero;
	
};

