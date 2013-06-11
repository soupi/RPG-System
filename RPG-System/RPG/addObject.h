#pragma once

#include "Script.h"

class LocalMap;
class GameObject;

class addObjScript : public Script
{
public:
	addObjScript(LocalMap& localmap, shared_ptr<GameObject>& obj, const sf::Vector2f& pos) : _localmap(localmap), _obj(obj), _pos(pos) { }
	virtual bool handleEvents(const Control& controls) { return false; }
	virtual bool Update(Controller&, float elapsedTime);
	virtual void Render(Controller& ctrl) {}
private:
	virtual void enter(Hero& hero) {}
	virtual void exit() {}

	LocalMap& _localmap;
	shared_ptr<GameObject> _obj;
	sf::Vector2f _pos;
};