#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"
#include "StateParams.h"
#include "Flag.h"
#include "Map.h"
#include "GameObject.h"
#include "LocalObject.h"
#include "Script.h"
#include <queue>

using std::queue;
using std::shared_ptr;

class LocalMap : public State
{
public:
	LocalMap();
	virtual State* Enter(shared_ptr<StateParams>& params) { init(params); return this; }
	virtual bool handleEvents(const Control& controls);
	virtual void Update(Controller& ctrl, float elapsedTime);
	virtual void Render(Controller& ctrl);
	shared_ptr<Map> map() const { return _map; }
	void addScript(shared_ptr<Script>& script);
	void NextScript(Controller& ctrl);

private:
	Flag _change_state;
	queue<shared_ptr<Script>> _scripts;
	void init(shared_ptr<StateParams>& params);
	shared_ptr<Map> _map;
};