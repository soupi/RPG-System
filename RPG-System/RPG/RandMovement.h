#pragma once

#include "Movement.h"

class RandMovement : public Movement
{
public:
	RandMovement(float time_between_moves, sf::Vector2f pos = sf::Vector2f(0.f, 0.f), unsigned speed = DEFAULT_SPEED) : Movement(pos, speed), _next_move_timer(5.f), 
		_time_between_moves(time_between_moves), _moving_duration_timer(0.f) { }
	virtual void handleEvents(const Control& controls);
	virtual void Update(LocalMap& localmap, GameObject& my_obj, Graphics& my_graphics, float elapsedTime);

private:
	float _next_move_timer;
	float _moving_duration_timer;
	float _time_between_moves;
	sf::Vector2f _curr_dir;
};