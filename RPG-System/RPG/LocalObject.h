#pragma once

#include "GameObject.h"
#include "Script.h"


class LocalObject : public GameObject
{
public:
	LocalObject(shared_ptr<Script> script, Graphics* graphics = new NoGraphics, Movement* movement = new NoMovement,
		bool passable = true) : GameObject(graphics, movement), _passable(passable), _script(script) {}

private:
	bool _passable;
protected:
	shared_ptr<Script> _script;
};