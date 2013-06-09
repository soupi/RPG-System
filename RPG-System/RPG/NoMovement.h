#pragma once

#include "Movement.h"

class NoMovement : public Movement
{
public:
	virtual void handleEvents(const Control& controls) { }
	virtual void Update(LocalMap& localmap, GameObject& my_obj, Graphics& my_graphics, float elapsedTime) ;
};