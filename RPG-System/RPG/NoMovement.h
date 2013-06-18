#pragma once

// no movement

#include "Movement.h"

class NoMovement : public Movement
{
public:
	virtual void handleEvents(const Control& controls) { }
	virtual bool Update(LocalMap& localmap, GameObject& my_obj, Graphics& my_graphics, float elapsedTime) { return false; }
};