// follow id movement

#pragma once

#include "FollowIdMovement.h"

class EyeFollowIdMovement : public FollowIdMovement
{
public:
	EyeFollowIdMovement(int id, float radius, float speed = DEFAULT_SPEED/1.2f) : FollowIdMovement(id, radius, speed)
		 { }
	virtual bool Update(LocalMap& localmap, GameObject& my_obj, Graphics& my_graphics, float elapsedTime);
};