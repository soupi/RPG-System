#pragma once

// representation of the hero on the map.

#include "GameObject.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include "HeroData.h"
#include "Enemy.h"
#include "Flag.h"
#include "AttackFactory.h"
#include "BasicAttack.h"
#include "BulletAttack.h"
#include <vector>
#include "Control.h"

using std::shared_ptr;
using std::vector;

class HeroCharacter : public GameObject
{
public:
	HeroCharacter(shared_ptr<HeroData>& data);
	virtual void handleEvents(const Control& controls);
	virtual void Update(Controller& ctrl, LocalMap& localmap, float elapsedTime);

	// ----- collision handling -----
	bool act(LocalMap& localmap, GameObject& obj) { return obj.act(localmap, *this); }
	void StepOn(LocalMap& localmap, GameObject& obj) { obj.StepOn(localmap, *this); }
	bool canStepOn(GameObject& obj) { return obj.canStepOn(*this); }

	bool act(LocalMap& localmap, LocalObject& obj);
	bool act(LocalMap& localmap, Enemy& obj);
	void StepOn(LocalMap& localmap, Enemy& obj) { obj.StepOn(localmap, *this); }

	virtual bool canStepOn(LocalObject& obj) { return false; }
	virtual bool canStepOn(Enemy& obj) { return false; }
	// ---------------------------
	void attack(const Stats& stats, int power); // hero is attacked

	virtual void setId(int id) { GameObject::setId(0); }
	void giveQuestItem(QuestItem& item);
	bool hasQuestItem(const string& item_name);
	// get loot
	void Loot(LocalMap& localmap, unsigned exp, unsigned coins) { _hero_data->Loot(localmap, *this, exp, coins); }

	void addNewAttack(shared_ptr<AttackFactory> atk);

	// makes the hero stop in place
	void stop() 
	{ 
		bool controls[NUM_OF_CONTROLS] = { false };
		handleEvents(Control(controls));
	}

private:
	Flag _act; // has the user pressed A?

	float _B_clock; // so there won't be "double" pressing on C or D buttons

	shared_ptr<HeroData> _hero_data; // reference of it's data
	float _hurt_timer;
	bool _ishurt;

	unsigned _curr_attack; // current marked attack

	vector<shared_ptr<AttackFactory>> _atks; // attacks
};