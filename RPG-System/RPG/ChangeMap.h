#pragma once

// this script changes the map to a new map

#include "Script.h"
#include <string>
#include <memory>
#include "Controller.h"
#include "ParamsMap.h"
#include "FadeEffect.h"

using std::string;

class ChangeMap : public Script
{
public:
	ChangeMap(const string& map, unsigned loc) : _map_name(map), _loc(loc) { }
	virtual bool handleEvents(const Control& controls) { return Continue(); }
	virtual bool Update(Controller& ctrl, float elapsedTime);
	virtual void Render(Controller& ctrl) { _fade.render(ctrl); }

private:
	string _map_name;
	unsigned _loc;
	Fade _fade;

	// enter state: stop the hero's movement and fade out
	virtual void enter(Hero& hero) { hero.getHeroForMap()->stop(); _fade.fadeOut(); }
	virtual void exit() {  }
};