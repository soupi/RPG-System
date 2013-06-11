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
	virtual void act(LocalMap& localmap, GameObject& obj) { obj.act(localmap, *this); }
	virtual void StepOn(LocalMap& localmap, GameObject& obj) { obj.StepOn(localmap, *this); }
	virtual bool canStepOn(GameObject& obj) { return obj.canStepOn(*this); }

	virtual bool canStepOn(LocalObject& obj) { return true; }
	virtual bool canStepOn(HeroCharacter& obj) { return true; }
	virtual bool canStepOn(Enemy& obj) { return true; }

	virtual void act(LocalMap& localmap, LocalObject& obj);
	virtual void act(LocalMap& localmap, Enemy& obj);
	virtual void act(LocalMap& localmap, HeroCharacter& obj);
	virtual void attack(LocalMap& localmap, LocalObject& obj);
	void attack(LocalMap& localmap, Enemy& obj);
	void attack(LocalMap& localmap, HeroCharacter& obj);

private:
	Stats _stats;
	int _power;
	shared_ptr<AttackAgainst> _atk;
};