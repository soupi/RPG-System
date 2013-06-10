// follow id movement

#pragma once

#include "Movement.h"

class FollowIdMovement : public Movement
{
public:
	FollowIdMovement(int id, float radius, sf::Vector2f pos = sf::Vector2f(0.f, 0.f), float speed = DEFAULT_SPEED/2.f) : Movement(pos, speed), 
		_id_to_follow(id), _radius(radius) 
		 { }
	virtual void handleEvents(const Control& controls);
	virtual void Update(LocalMap& localmap, GameObject& my_obj, Graphics& my_graphics, float elapsedTime);

private:
	int _id_to_follow;
	float _radius;
	sf::Vector2f _curr_dir;
};