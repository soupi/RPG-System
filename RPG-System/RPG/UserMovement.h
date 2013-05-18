#pragma once

#include "Movement.h"

class UserMovement : public Movement
{
public:
	UserMovement() : _run(false) { }
	virtual void handleEvents(const Control& controls);
	virtual void Update(Graphics* _graphics, float elapsedTime);

private:
	bool _run;
};