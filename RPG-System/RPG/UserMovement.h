#pragma once

#include "Movement.h"

class UserMovement : public Movement
{
public:
	UserMovement() : _run(false), _dir(0.f,0.f) { }
	virtual void handleEvents(const Control& controls);
	virtual void Update(LocalMap& localmap, GameObject& my_obj, Graphics& my_graphics, float elapsedTime);

private:
	bool _run;
	sf::Vector2f _dir;
};