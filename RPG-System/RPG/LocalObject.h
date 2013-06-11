#pragma once

#include "GameObject.h"
#include "Script.h"
#include "Attack.h"


class LocalObject : public GameObject
{
public:
	LocalObject(shared_ptr<Script> script, Graphics* graphics = new NoGraphics, Movement* movement = new NoMovement,
		bool passable = false) : GameObject(graphics, movement), _passable(passable), _script(script) {}
	virtual ~LocalObject() {}

	virtual void act(LocalMap& localmap, GameObject& obj) { obj.act(localmap, *this); }
	virtual void StepOn(LocalMap& localmap, GameObject& obj) { obj.StepOn(localmap, *this); }
	virtual bool canStepOn(GameObject& obj) { return obj.canStepOn(*this); }

	virtual bool canStepOn(LocalObject& obj) { return _passable; }
	virtual bool canStepOn(HeroCharacter& obj) { return _passable; }
	virtual bool canStepOn(Enemy& obj) { return _passable; }
	virtual bool canStepOn(Attack& obj) { return _passable; }

	void act(LocalMap& localmap, HeroCharacter&);



private:
	bool _passable;
protected:
	shared_ptr<Script> _script;
};