#pragma once

// this script removes an object from the map

#include "Script.h"

class LocalMap;
class GameObject;

class remObjScript : public Script
{
public:
	remObjScript(LocalMap& localmap, GameObject* obj) : _localmap(localmap), _obj(obj) { }
	virtual bool handleEvents(const Control& controls) { return false; }
	virtual bool Update(Controller&, float elapsedTime);
	virtual void Render(Controller& ctrl) {}
private:
	virtual void enter(Hero& hero) {}
	virtual void exit() {}

	LocalMap& _localmap;
	GameObject* _obj; // object to remove
};