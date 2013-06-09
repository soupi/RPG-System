#pragma once

#include "Script.h"
#include <string>
#include <memory>
#include "Controller.h"
#include "ParamsMap.h"

using std::string;

class ChangeMap : public Script
{
public:
	ChangeMap(const string& map, unsigned loc) : _map_name(map), _loc(loc) { }
	virtual bool handleEvents(const Control& controls) { return Continue(); }
	virtual bool Update(Controller& ctrl, float elapsedTime) 
	{ 
		ctrl.getStateMachine().Change("localmap", shared_ptr<StateParams>(new ParamsMap(ctrl, _map_name, _loc)));
		_continue = false;
		return _continue;
	} 
	virtual void Render(Controller& ctrl) 
	{

	}

private:
	string _map_name;
	unsigned _loc;

	virtual void enter(Hero& hero) {  }
	virtual void exit() {  }
};