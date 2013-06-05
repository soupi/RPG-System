#pragma once

#include "GameObject.h"
#include "Attack.h"
#include "Stats.h"

class Enemy : GameObject
{
public:
	Enemy(Graphics* graphics = new NoGraphics, Movement* movement = new NoMovement) : GameObject(graphics, movement) {}
	virtual void act(LocalMap& localmap, GameObject& obj) { obj.act(localmap, *this); }
	virtual void StepOn(LocalMap& localmap, GameObject& obj) { obj.StepOn(localmap, *this); }
	virtual bool canStepOn(GameObject& obj) { return obj.canStepOn(*this); }

	virtual bool canStepOn(LocalObject& obj) { return false; }
	virtual bool canStepOn(HeroCharacter& obj) { return true; }
	virtual bool canStepOn(Enemy& obj) { return true; }

	void act(LocalMap& localmap, HeroCharacter& hero);
private:
	int _HP;
	Stats _stats;
};