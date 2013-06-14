// follow id movement

#pragma once

#include "Movement.h"

class FollowIdMovement : public Movement
{
public:
	FollowIdMovement(int id, float radius, float speed = DEFAULT_SPEED/1.2f) : Movement(speed), 
		_id_to_follow(id), _radius(radius) 
		 { }
	virtual void handleEvents(const Control& controls){}
	virtual bool Update(LocalMap& localmap, GameObject& my_obj, Graphics& my_graphics, float elapsedTime);

private:
	int _id_to_follow;
	float _radius;
	sf::Vector2f _curr_dir;

protected:
	void setDir(LocalMap& localmap, GameObject& my_obj);
};