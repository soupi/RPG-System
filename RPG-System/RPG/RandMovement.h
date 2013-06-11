// random movement

#pragma once

#include "Movement.h"

class RandMovement : public Movement
{
public:
	RandMovement(float time_between_moves, float speed = DEFAULT_SPEED) : Movement(speed), _next_move_timer(5.f), 
		_time_between_moves(time_between_moves), _moving_duration_timer(0.f) { }
	virtual void handleEvents(const Control& controls);
	virtual bool Update(LocalMap& localmap, GameObject& my_obj, Graphics& my_graphics, float elapsedTime);

private:
	float _next_move_timer;
	float _moving_duration_timer;
	float _time_between_moves;
	sf::Vector2f _curr_dir;
};