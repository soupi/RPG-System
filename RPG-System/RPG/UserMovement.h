#pragma once

#include "Movement.h"

class UserMovement : public Movement
{
public:
	UserMovement() : _run(false) { }
	virtual void handleEvents(const Control& controls);
	virtual sf::Vector2f Update(LocalMap& localmap, GameObject& my_obj, float elapsedTime);

private:
	bool _run;
};