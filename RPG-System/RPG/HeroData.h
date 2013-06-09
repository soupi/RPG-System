#pragma once

#include "Stats.h"
#include "QuestItem.h"

#include <string>
#include <map>
#include "Bar.h"

class LocalMap;


const unsigned BASE_HP = 100;
const unsigned BASE_LIVES = 2;

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
	void Loot(LocalMap& localmap, unsigned exp, unsigned coins) { _exp += exp; _coins += coins; checkLevelRaise(localmap); }

private:
	unsigned _exp;
	unsigned _level;
	unsigned _coins;
	std::map<std::string, QuestItem> _quest_items;
	
	int _HP;
	int _Lives;
	Stats _stats;

	Bar _HP_bar;

	void checkLevelRaise(LocalMap& map);
};