#pragma once

#include "GameObject.h"
#include "Script.h"


class LocalObject : public GameObject
{
public:
	LocalObject(shared_ptr<Script> script, Graphics* graphics = new NoGraphics, Movement* movement = new NoMovement,
		bool passable = false) : GameObject(graphics, movement), _passable(passable), _script(script) {}

	void act(LocalMap& localmap, GameObject& obj) { obj.act(localmap, *this); }
	void StepOn(LocalMap& localmap, GameObject& obj) { obj.StepOn(localmap, *this); }
	bool canStepOn(GameObject& obj) { return obj.canStepOn(*this); }

private:
	bool _passable;
protected:
	shared_ptr<Script> _script;
};