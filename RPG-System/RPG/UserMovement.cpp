#include "UserMovement.h"
#include "Tile.h"
#include "LocalMap.h"
#include "GameObject.h"

sf::Vector2f operator*(int scalar, sf::Vector2f vec)
{
	return sf::Vector2f(scalar*vec.x, scalar*vec.y);
}

void UserMovement::handleEvents(const Control& controls)
{

	if (controls.isPressed(RIGHT))
		_direction.x = 1;
	else if (controls.isPressed(LEFT))
		_direction.x = -1;
	else _direction.x = 0;

	if (controls.isPressed(UP))
		_direction.y = -1;
	else if (controls.isPressed(DOWN))
		_direction.y = 1;
	else _direction.y = 0;

	// toggle run mode
	if (controls.isPressed(B))
		_run = true;
	else _run = false;
}

sf::Vector2f UserMovement::Update(LocalMap& localmap, GameObject& my_obj, float elapsedTime)
{
	if (_newpos)
	{
		my_obj.getGraphics()->setPos(_pos);

		_newpos = false; 
	}

	int scalar = SCRN_TILE_SIZE;
	if (_run)
		scalar = 2*SCRN_TILE_SIZE;

	_lastpos = _pos;

	sf::Vector2f temp_pos = _pos;
	temp_pos.x += scalar * _speed * _direction.x  * elapsedTime;
	if (!localmap.map()->canStepOn(my_obj))
		temp_pos.x = _pos.x;

	temp_pos.y += scalar * _speed * _direction.y  * elapsedTime;
	if (!localmap.map()->canStepOn(my_obj))
		temp_pos.y = _pos.y;

	if (_pos == temp_pos)
		return _pos;


	_direction.x = (temp_pos.x - _pos.x) ? _direction.x : 0;
	_direction.y = (temp_pos.y - _pos.y) ? _direction.y : 0;
	_pos = temp_pos;

	my_obj.getGraphics()->move(scalar * _speed * _direction * elapsedTime);

	return my_obj.getGraphics()->getPos();
}