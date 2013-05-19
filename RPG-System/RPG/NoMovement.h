#pragma once

#include "Movement.h"

class NoMovement : public Movement
{
public:
	virtual void handleEvents(const Control& controls) { }
	virtual void Update(Graphics* _graphics, float elapsedTime) { }
};