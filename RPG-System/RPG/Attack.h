#pragma once

#include "GameObject.h"
#include "Stats.h"
#include "AttackAgainst.h"

class Attack : public GameObject
{
public:
	Attack(Stats stats, int power, AttackAgainst* atk = new AttackAll, Graphics* graphics = new NoGraphics, 
		Movement* movement = new NoMovement) : 
	  GameObject(graphics, movement), _stats(stats), _power(power), _atk(atk) {}

	virtual ~Attack() {}
	void act(LocalMap& localmap, GameObject& obj) { obj.act(localmap, *this); }
	void StepOn(LocalMap& localmap, GameObject& obj) { obj.StepOn(localmap, *this); }
	bool canStepOn(GameObject& obj) { return obj.canStepOn(*this); }

	virtual bool canStepOn(LocalObject& obj) { return false; }
	virtual bool canStepOn(HeroCharacter& obj) { return true; }
	virtual bool canStepOn(Enemy& obj) { return true; }

	void StepOn(LocalMap& localmap, LocalObject& obj);
	void StepOn(LocalMap& localmap, Enemy& obj);
	void StepOn(LocalMap& localmap, HeroCharacter& obj);
	virtual void attack(LocalMap& localmap, LocalObject& obj);
	void attack(LocalMap& localmap, Enemy& obj);
	void attack(LocalMap& localmap, HeroCharacter& obj);

private:
	Stats _stats;
	int _power;
	shared_ptr<AttackAgainst> _atk;
};