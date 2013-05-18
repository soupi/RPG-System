#pragma once

#include "Control.h"
#include "Controller.h"
#include "Map.h"
#include "Movement.h"


class Movement;

class Action
{
public:
	~Action() { }
	virtual void handleEvents(const Control& controls) = 0;
	virtual void Update(Controller& ctrl, Map& map, float elapsedTime, Movement* movement) = 0;
};