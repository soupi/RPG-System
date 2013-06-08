#include "RandMovement.h"
#include "Tile.h"
#include "LocalMap.h"
#include "GameObject.h"
#include "Utility.h"


void RandMovement::handleEvents(const Control& controls)
{

}

void RandMovement::Update(LocalMap& localmap, GameObject& my_obj, float elapsedTime)
{
	if (_newpos)
	{
		my_obj.getGraphics()->setPos(_init_pos);

		_newpos = false; 
	}

	_next_move_timer -= elapsedTime;
	_moving_duration_timer -= elapsedTime;

	if (_next_move_timer <= 0)
	{
		_direction.x = float(rand() % 3 -1);
		_direction.y = float(rand() % 3 -1);
		_next_move_timer = _time_between_moves;
		_moving_duration_timer = 1.f;
	}

	if (_moving_duration_timer > 0)
		return;


	if (isZero(_direction))
		return;

	my_obj.getGraphics()->setDir(_direction);

	int scalar = SCRN_TILE_SIZE;

	sf::Vector2f temp_dir(scalar * _speed * _direction.x  * elapsedTime, 0);
	my_obj.getGraphics()->move(temp_dir);

	if (!localmap.map()->canStepOn(my_obj))
	{
		my_obj.getGraphics()->undo_move();
	}

	temp_dir.y = scalar * _speed * _direction.y  * elapsedTime;
	temp_dir.x = 0;
	my_obj.getGraphics()->move(temp_dir);
	if (!localmap.map()->canStepOn(my_obj))
	{
		my_obj.getGraphics()->undo_move();
	}

	localmap.map()->Step(localmap, my_obj);

}