#pragma once

#include "GameObject.h"
#include "Stats.h"

class Attack : public GameObject
{
public:
	Attack(Stats stats, unsigned power, Graphics* graphics = new NoGraphics, Movement* movement = new NoMovement) : 
	  GameObject(graphics, movement), _stats(stats), _power(power) {}

	virtual ~Attack() {}
	void act(LocalMap& localmap, GameObject& obj) { obj.act(localmap, *this); }
	void StepOn(LocalMap& localmap, GameObject& obj) { obj.StepOn(localmap, *this); }
	bool canStepOn(GameObject& obj) { return obj.canStepOn(*this); }

	virtual bool canStepOn(LocalObject& obj) { return false; }
	virtual bool canStepOn(HeroCharacter& obj) { return true; }
	virtual bool canStepOn(Enemy& obj) { return true; }

	void StepOn(LocalMap& localmap, LocalObject& obj);

private:
	Stats _stats;
	unsigned _power;
};