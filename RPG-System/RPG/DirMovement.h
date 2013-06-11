#pragma once
#include "Movement.h"

class DirMovement : public Movement
{
public:
	DirMovement(const sf::Vector2f& dir, float speed = DEFAULT_SPEED) : Movement(speed), _dir(dir) { }
	virtual void handleEvents(const Control& controls){}
	virtual bool Update(LocalMap& localmap, GameObject& my_obj, Graphics& my_graphics, float elapsedTime);

private:
	sf::Vector2f _dir;
};