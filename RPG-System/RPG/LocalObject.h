#pragma once

#include "GameObject.h"
//#include "Script.h"


class LocalObject : public GameObject
{
public:
	LocalObject(Graphics* graphics = new NoGraphics, Movement* movement = new NoMovement, bool passable = true) : GameObject(graphics, movement) _passable(passable) {}
	
	virtual void Interact(LocalMap& localmap, GameObject& obj);
	// double dispatch
	virtual void StepOn(LocalMap& localmap, GameObject& obj);
	virtual bool canStepOn(GameObject& obj);

private:
	bool _passable;
	//Script* _script;
};