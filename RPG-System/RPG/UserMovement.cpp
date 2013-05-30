#include "UserMovement.h"
#include "Tile.h"
#include "LocalMap.h"
#include "GameObject.h"

sf::Vector2f operator*(int scalar, sf::Vector2f vec)
{
	return sf::Vector2f(scalar*vec.x, scalar*vec.y);
}
bool isZero(sf::Vector2f vec)
{
	return (vec.x == 0.f && vec.y == 0.f) ? true : false;
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

void UserMovement::Update(LocalMap& localmap, GameObject& my_obj, float elapsedTime)
{
	if (_newpos)
	{
		my_obj.getGraphics()->setPos(_init_pos);

		_newpos = false; 
	}

	if (isZero(_direction))
		return;

	my_obj.getGraphics()->setDir(_direction);

	int scalar = SCRN_TILE_SIZE;
	if (_run)
		scalar = 2*SCRN_TILE_SIZE;

	sf::Vector2f temp_dir(scalar * _speed * _direction.x  * elapsedTime, 0);
	my_obj.getGraphics()->move(temp_dir);

	if (!localmap.map()->canStepOn(my_obj))
	{
		my_obj.getGraphics()->undo_move();
		_direction.x = 0;
	}

	temp_dir.y = scalar * _speed * _direction.y  * elapsedTime;
	temp_dir.x = 0;
	my_obj.getGraphics()->move(temp_dir);
	if (!localmap.map()->canStepOn(my_obj))
	{
		my_obj.getGraphics()->undo_move();
		_direction.y = 0;
	}

	localmap.map()->Step(localmap, my_obj);

}