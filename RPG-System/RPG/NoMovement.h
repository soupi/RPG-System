#pragma once

#include "Movement.h"

class NoMovement : public Movement
{
public:
	virtual void handleEvents(const Control& controls) { }
	virtual void Update(LocalMap& localmap, Graphics* _graphics, float elapsedTime) { }
};