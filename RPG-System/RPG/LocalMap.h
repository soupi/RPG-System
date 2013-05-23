#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"
#include "StateParams.h"
#include "Flag.h"
#include "Map.h"
#include "GameObject.h"
#include "LocalObject.h"

class LocalMap : public State
{
public:
	LocalMap();
	virtual State* Enter(StateParams* params) { init(params); return this; }
	virtual bool handleEvents(const Control& controls);
	virtual void Update(Controller& ctrl, float elapsedTime);
	virtual void Render(Controller& ctrl);

private:
	Flag _change_state;

	void init(StateParams* params);

	Map* _map;
};