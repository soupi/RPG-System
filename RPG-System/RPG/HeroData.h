#pragma once

// data of the hero: experience, level, num of coins, quest items, hp, stats and so on

#include "Stats.h"
#include "QuestItem.h"

#include <string>
#include <map>
#include "Bar.h"

class LocalMap;
class HeroCharacter;

const unsigned BASE_HP = 200;
const unsigned BASE_LIVES = 0;

class HeroData
{
public:
	HeroData() : _HP(BASE_HP), _Lives(BASE_LIVES), _exp(0), _level(0), _coins(0), _HP_bar(BASE_HP) {}
	bool isAlive() const { return (_Lives >= 0); }

	const unsigned heroLevel() const { return _level; }
	bool hasQuestItem(const string& name) { return (_quest_items.find(name) != _quest_items.end()); }
	void addQuestItem(QuestItem& item) { _quest_items.insert(make_pair(item.name(), item)); }
	void takeDamage(unsigned amount);
	const Stats& getStats() const { return _stats; }
	void showHP(Controller& ctrl);
	void Loot(LocalMap& localmap, HeroCharacter& hero_char, unsigned exp, unsigned coins) { _exp += exp; _coins += coins; checkLevelRaise(localmap, hero_char); }

private:
	unsigned long _exp;
	unsigned long _level;
	unsigned long _coins;
	std::map<std::string, QuestItem> _quest_items;
	
	int _HP;
	int _Lives;
	Stats _stats;

	Bar _HP_bar;

	void checkLevelRaise(LocalMap& map, HeroCharacter& hero_char);
};