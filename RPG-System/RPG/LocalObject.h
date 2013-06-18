#pragma once

// a local object for map.

#include "GameObject.h"
#include "Script.h"
#include "Attack.h"

class LocalObject : public GameObject
{
public:
	// constructor: needs the script the object runs, the graphics, the movement and if it's passable or not
	LocalObject(shared_ptr<Script> script, Graphics* graphics = new NoGraphics, Movement* movement = new NoMovement,
		bool passable = false) : GameObject(graphics, movement), _passable(passable), _script(script) {}
	virtual ~LocalObject() {}

	virtual bool act(LocalMap& localmap, GameObject& obj) { return obj.act(localmap, *this); }
	virtual void StepOn(LocalMap& localmap, GameObject& obj) { obj.StepOn(localmap, *this); }
	virtual bool canStepOn(GameObject& obj) { return obj.canStepOn(*this); }

	virtual bool canStepOn(LocalObject& obj) { return _passable; }
	virtual bool canStepOn(HeroCharacter& obj) { return _passable; }
	virtual bool canStepOn(Enemy& obj) { return _passable; }
	virtual bool canStepOn(Attack& obj) { return _passable; }

	bool act(LocalMap& localmap, HeroCharacter&);



private:
	bool _passable;
protected:
	shared_ptr<Script> _script;
};