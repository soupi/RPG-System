#include "Movement.h"
#include "Utility.h"
#include "GameObject.h"
#include "LocalMap.h"


// update movement
bool Movement::Update(LocalMap& localmap, GameObject& my_obj, Graphics& my_graphics, float elapsedTime)
{
	// if direction is zero stop and return.
	if (isZero(_direction))
		return false; 

	// set current graphical direction of movement
	my_graphics.setDir(_direction);

	sf::Vector2f last = my_obj.getPos();

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

	return !(last == my_obj.getPos());
}