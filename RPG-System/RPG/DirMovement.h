#pragma once
#include "Movement.h"

class DirMovement : public Movement
{
public:
	DirMovement(sf::Vector2f& dir, sf::Vector2f pos = sf::Vector2f(0.f, 0.f), float speed = DEFAULT_SPEED/2.f) : Movement(pos, speed), 
		_dir(dir) { }
	virtual void handleEvents(const Control& controls);
	virtual void Update(LocalMap& localmap, GameObject& my_obj, Graphics& my_graphics, float elapsedTime);

private:
	sf::Vector2f _dir;
};