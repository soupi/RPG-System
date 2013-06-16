#pragma once

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

	void act(LocalMap& localmap, GameObject& obj) { obj.act(localmap, *this); }
	void StepOn(LocalMap& localmap, GameObject& obj) { obj.StepOn(localmap, *this); }
	bool canStepOn(GameObject& obj) { return obj.canStepOn(*this); }

	void act(LocalMap& localmap, LocalObject& obj);
	void act(LocalMap& localmap, Enemy& obj);
	void StepOn(LocalMap& localmap, Enemy& obj) { obj.StepOn(localmap, *this); }

	virtual bool canStepOn(LocalObject& obj) { return false; }
	virtual bool canStepOn(Enemy& obj) { return false; }

	void attack(const Stats& stats, int power);

	void giveQuestItem(QuestItem& item);
	bool hasQuestItem(const string& item_name);
	void Loot(LocalMap& localmap, unsigned exp, unsigned coins) { _hero_data->Loot(localmap, *this, exp, coins); }
	virtual void setId(int id) { GameObject::setId(0); }

	void addNewAttack(shared_ptr<AttackFactory> atk);

	void stop() 
	{ 
		bool controls[NUM_OF_CONTROLS] = { false };
		//Control con(controls);
		handleEvents(Control(controls));
	}

private:
	Flag _act;
	Flag _attack1;
	Flag _attack2;

	float _B_clock;
	shared_ptr<HeroData> _hero_data;
	float _hurt_timer;
	bool _ishurt;

	unsigned _curr_attack;

	vector<shared_ptr<AttackFactory>> _atks;
};