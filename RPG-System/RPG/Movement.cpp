#include "Movement.h"
#include "Utility.h"
#include "GameObject.h"
#include "LocalMap.h"


// update movement
void Movement::Update(LocalMap& localmap, GameObject& my_obj, Graphics& my_graphics, float elapsedTime)
{
	// set new pos
	if (_newpos)
	{
		my_graphics.setPos(_init_pos);
		_newpos = false; 
	}

	// if direction is zero stop and return.
	if (isZero(_direction))
		return;

	// set current graphical direction of movement
	my_graphics.setDir(_direction);

	// try moving on x
	sf::Vector2f temp_dir(_speed * _direction.x  * elapsedTime, 0);
	my_graphics.move(temp_dir);

	// check if move is valid
	if (!localmap.canStepOn(my_obj))
		my_graphics.undo_move();

	// try moving on y
	temp_dir.y = _speed * _direction.y  * elapsedTime;
	temp_dir.x = 0;
	my_graphics.move(temp_dir);
	// check if move is valid
	if (!localmap.canStepOn(my_obj))
		my_graphics.undo_move();

	localmap.Step(my_obj);

}