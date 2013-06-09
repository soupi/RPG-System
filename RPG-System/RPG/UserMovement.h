// user controlled movement

#pragma once

#include "Movement.h"

class UserMovement : public Movement
{
public:
	UserMovement() : _run(false),  _curr_speed(HERO_SPEED) { }
	virtual void handleEvents(const Control& controls);
	virtual void Update(LocalMap& localmap, GameObject& my_obj, Graphics& my_graphics, float elapsedTime);

private:
	bool _run;
	float _curr_speed;
};