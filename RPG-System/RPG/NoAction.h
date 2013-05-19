#pragma once

#include "Action.h"

class NoAction : public Action
{
public:
	virtual void handleEvents(const Control&) {}
	virtual void Update(Controller&, Map&, float, Movement*) {}
};